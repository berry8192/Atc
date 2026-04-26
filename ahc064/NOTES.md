# AHC064 調査ノート

貨物車両並べ替え (R=10, 各出発線 10両/容量15、各待避線 容量20、最大4000ターン)。
解けたとき `5000 - T` 点、150 ケース合計。

## 改善履歴 (100 seeds avg)

| ver | avg | T avg | Δ | 内容 |
|---|---|---|---|---|
| baseline (B.cc beam) | 326 | – | – | ビームサーチ、解けず部分点のみ |
| C.cc 初版 | 4823 | 177 | +4497 | 全展開 + 順次組立 (selection sort 風) |
| + 非交差優先 displace | 4837 | 163 | +14 | op0_put が op1_push と同ターンに乗るペア優先 |
| + smart pack | 4847 | 153 | +10 | 各 op を「conflict 外で最も早いターン」へ |
| + interleave (round-robin) | **4869** | **131** | +22 | 全 line を 1 ラウンドで 1 v ずつ進める |
| **C.cc 確定** | **4869** | **131** | – | コミット 83dcddf |
| D.cc 初版 (user 主導) | 4883 | 117 | +14 | min-cost ライン選び + half-bias + 連番形成 |
| F.cc (D + 乱択 4 段階) | 4910 | 90 | +27 | NOISE = 1k/5k/20k/50k 循環、~12k試行 |
| **F.cc (2 段階)** | **4911** | **89** | +1 | NOISE = 1k/5k のみ。コミット e1b7656 |
| + chain ノイズ | 4910 | – | -1 | chain 延長を確率で打ち切り (1/5) |
| + chunk + chain ノイズ | 4905 | – | -6 | displace の chunk も確率で分割 (1/4) |

## 現役ベスト: F.cc (avg 4911 / T avg 89)

### Phase 1
全 D[r] を Sd[r] に 1 ターンで dump（10 op が j=r の恒等で非交差なので並列）。

### Phase 2 (run_solver)
- 各イテレーションで **コスト最小 r** を選択。
  - cost = `d * 1000 - L * 100` + ノイズ（d=深さ, L=chain長）
- 選んだ v について:
  - d > 0 なら `displace(j, d, target_r)` で他 siding へ退避（D[m] 経由 1 round trip = 2 ops）
  - chain extension で連続 ID v..v+L-1 を 1 op で push
- displace の (m, k_dest) は plan_disp で評価:
  - `chunk * 100000` (大チャンク優先)
  - `m != target_r` で +50000 (op0_put と op1_push が別 line)
  - 非交差ペアで +100000 (smart pack で同ターン梱包可)
  - half-bias: target_r の半分 (low/high) と同半分の k +20000、m +5000
  - 連番形成: 退避 chunk の末尾と Sd[k] head が同 target_r 連番で +40000/run
  - 空 siding +1000、size ペナルティ -10/item、min-ID ボーナス
  - **NOISE 加算** (1000 or 5000)

### packing
smart pack: 各 op を `last_line[i]`/`last_sid[j]` 制約下で「最も早い valid ターン」に。

### main loop (乱択再試行)
- baseline (NOISE=0) を 1 回走らせて初期 best 保持
- 時間制限 (1.85s) まで NOISE = 1000 と 5000 を交互、毎回 best を更新
- 1 試行 約 0.15ms、典型 12000+ 試行/seed

## ノイズレベル別効果分析 (100 seeds)

`F_dbg.cc` で各 NOISE が「最終 best を生んだ」回数を計測:

| NOISE | 最終 best 勝者 | 全試行 update 数 | avg min_T |
|---|---|---|---|
| 0 (baseline) | **0** | – | 116.2 |
| 1000 | 37 | 294 | 91.4 |
| 5000 | **56** | 391 | **90.5** |
| 20000 | 7 | 52 | 95.3 |
| 50000 | 0 | 5 | 99.8 |

**観察**:
- NOISE=5000 が sweet spot、1000 が補助
- 20k/50k はほぼ寄与なし → 削除して 1k/5k に集中させたら +1 の改善 (4910 → 4911)
- 決定論 baseline は 100 seeds **全て**で乱択に負ける → 乱択が必須

## 効果のなかった試行（記録）

### min-depth-first 処理順
round-robin の代わりに「次車両の depth が最小の line」を優先。avg 4868、ほぼ中立。
理由: smart pack が op の順序を吸収するので、生成順による差が小さい。

### v_next-aware displace 退避先選択
退避先 Sd[k] が他 line の next-needed v を含むなら大きなペナルティ。中立。
理由: 既存の half-bias と min-ID ボーナスがほぼ同等の役割。

### 案 C 完全版 (siding fixture)
v=99..0 の decreasing 順で Sd[r] head に push して最終的に op1(r, r, 10) で merge。
**correctness 問題で詰む**: 同一 line の複数 ID が初期 Sd[r] にいる場合 (確率 ~26%)、build 済み IDs が後続の displacement で破壊される。

### chain extension のランダム停止
chain 延長を確率 1/5 で途中停止。avg 4910 (-1)。
理由: chain は ops 削減 + smart pack の自由度両立してたので、削ると ops が増えて turn 数も微増。

### displace の chunk size ランダム分割
chunk を確率 1/4 で `1+rng()%remaining` に切る。avg 4905 (-6)。
理由: chunk weight (100k) を超える noise が必要だが、chunk 削減自体が ops を 2 倍以上に増やすので、smart pack で吸収しきれない。

## 残る改善方向

理論下限 T~50 (= ops 最小 + 完全 10 並列) に対して現状 89、まだ 40 ターン分の余地。

### A. 案 C 改良版 (s_r ≠ r な buffer)
各 line r の siding fixture を「初期に line-r ID を含まない Sd[s_r]」に置く。
- s_r 候補の確率: 1 line あたり ~33% で完全に 0 個、~74% で 0-1 個
- 単調 s_r が組めるかは seed 依存 → 場合によっては Phase 3 が複数 turn 化

### B. ハイブリッド上下構築
各 line を lower (10r..10r+4) + upper (10r+5..10r+9) に分割。
- lower は direct push、upper は siding fixture
- 触る resource (D vs Sd) が違うので並列度が上がる
- 実装中規模

### C. グローバルスケジューラ
smart pack を「依存グラフ + 並列スケジュール」に置き換え。可換 op 並べ替えを許す。
- ops 順を保つ制約を緩めて、依存関係だけ守る
- 実装中規模、効果 +5〜15

### D. 焼きなまし化 (Metropolis 受容)
greedy update を「確率的に悪化も受容」に変える。局所解抜け出し狙い。
- 実装軽量、効果不確実

## ファイル構成 (現在)

| file | 役割 | スコア |
|---|---|---|
| F.cc | 現役ベスト | avg 4911 (commit e1b7656) |
| D.cc | F の元 (deterministic) | avg 4883 (旧) ~ 4888 (現) |
| C.cc | 旧版 (round-robin) | avg 4869 (commit 83dcddf) |
| E.cc | user の pair-based 実験 | 未追跡 |
| B.cc | beam search | avg 326、放置 |
| A.cc | 入力読み雛形 | – |

## テスト方法

```bash
g++ -O2 -std=c++17 -o f.out F.cc
cp f.out b.out
bash test.sh 100      # 100 seeds, 約 3 分
```

`test.sh` は `external_tools/target/release/vis` でスコア算出、コンパクトなテーブル + summary を出力。
