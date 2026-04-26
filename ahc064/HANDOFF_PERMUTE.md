# 引き継ぎ: ラインの最終入れ替え戦略

別 Claude セッションへの引き継ぎ用ドキュメント。

## 背景: AHC064 の現状

- AHC064: 貨物車両並べ替え (R=10, 出発線容量15・初期10両, 待避線容量20・初期空, 最大4000ターン)
- スコア: 解けたら `5000 - T`、150 ケース合計
- 作業ディレクトリ: `/home/berry/Atc/ahc064`
- 詳細仕様: `probrem_statemant.md`、これまでの履歴: `NOTES.md`

### 現役ベスト
| 解 | avg (100 seeds) | T avg |
|---|---|---|
| F.cc | 4911 | 89 |
| **I.cc** (F + tuned weights) | **4913** | 約88 |

I.cc は F.cc に D.cc から得た重みチューニング (chain 形成 +40k→+150k、empty +1k→+30k、half-bias m +5k→+30k、find_next の chain bonus 削除) を適用したもの。

## 提案アイデア: ライン permutation + 最終入れ替え

### 動機
現在は line r に IDs `10r..10r+9` を組む（位置 r 固定）。**しかし最初から固定する必要はない**：
- 各 line で組みやすい 10 連番セットを選ぶ
- 全部組み終わった後、待避線経由で line 同士を **swap して位置を正しい r に揃える**
- ユーザのアイデア: "最後に待避線側を使って列ごと位置を変えればほんの数ターンで済みます。この数ターンよりも位置を最初から0,1,2,...としなくていいバリエーションのほうが有効に働くかもしれません"

### コスト試算
**Swap 1 回 (2-cycle) のコスト:**
- op0(i, k1, 10): line i → siding k1
- op0(j, k2, 10): line j → siding k2  ← turn 1 同時 (i<j, k1<k2 で非交差 OK)
- op1(j, k1, 10): siding k1 → line j  ← turn 2
- op1(i, k2, 10): siding k2 → line i  ← turn 3 (op1 ペアは k1<k2, i<j で非交差不成立 → 別 turn)

合計 **3 turn / swap**。

一般 permutation: cycle 分解、ランダム permutation の expected cycles ≈ 2.93 → 約 9 turn 余分。

3-cycle (a→b→c→a) なら：1 つを待避線に退避、玉突き式に動かす → 約 4-5 turn。

### 期待効果
- 各 line を最も組みやすい 10 連番に割り当てれば、displacement が減る
- 局所最適化で +数〜十数ターン節約の可能性
- ただし permutation cost が +5〜+15 turn かかるので、**ネットの効果は +0〜+10 程度** と想定（不確実）

### 実装計画
1. **permutation 選択**:
   - 入力 D[r] と initial Sd[r]=D[r] dump 後の状態から、各 candidate permutation π について「π を使った時の build cost 推定」を計算
   - 全 π = 10! = 3.6M で重い → ヒューリスティクス (greedy hungarian, local search)
   - 簡易版: 各 line r について「最も組みやすい連番セット (10s..10s+9)」を選んでマッチング
2. **build phase**:
   - 既存 F.cc/I.cc の run_solver() を generic 化: target_r=r で IDs `10*π(r)..10*π(r)+9` を組む
   - chain 形成ボーナス、cost 関数等は target_r 基準ではなく `IDs[π(r)]` 基準で評価
3. **permute phase**:
   - π の cycle 分解 → 各 cycle で待避線経由 swap
   - non-crossing pair が同 turn に入るよう順序計算
4. **smart pack**: 既存ロジックそのままで OK
5. **乱択再試行**: F.cc の枠組みで permutation も含めて多数試行

### 注意点
- π = identity (現状) を必ず候補に入れる: 現状以下にならないよう保険
- swap の通り道 (k1, k2) は非交差順序で慎重に選ぶ
- chain 形成等のボーナスは `target_r` ではなく `target_ids/10 == π(r)` で判定

## ファイル構成

| file | 役割 | 備考 |
|---|---|---|
| `F.cc` | 旧ベスト | avg 4911, commit e1b7656 |
| **`I.cc`** | **現役ベスト** | F + tuned weights, avg 4913 |
| `D.cc` | I の元 (deterministic) | 2-step lookahead 入り、avg 4888 |
| `G.cc` | 0/9 両側構築の試み | 失敗、forward-only に戻して放置 |
| `C.cc`, `E.cc`, `B.cc`, `A.cc` | 旧版 | NOTES.md 参照 |
| `NOTES.md` | 全体履歴・実装詳細 | **必読** |
| `probrem_statemant.md` | 問題仕様 | – |

## I.cc のコア構造（permutation 拡張時に変更点を追跡）

```cpp
// run_solver() 内、各イテレーション:
// 1. find_next(r): line r が次に欲しい car v = 10r + |D[r]| を探索
//    → permutation 適用: v = 10*π(r) + |D[r]|
// 2. plan_disp(): 退避先評価
//    → chain 形成ボーナス内 t_target = sk_top / 10 が引数 r ではなく π(r) に依存することに注意
```

`half_lo`/`half_hi` の half-bias も target_r ベース。π 適用時は `π(target_r) < 5 ? 0 : 5` でも良いが、待避線レイアウトは元のままなので **元の target_r で half-bias 維持** が無難。

## テスト方法

```bash
g++ -O2 -std=c++17 -o i.out I.cc
cp i.out b.out          # test.sh のデフォルトバイナリ
bash test.sh 100        # 100 seeds, 約 3 分 (1 seed 1.85s で時間制限)
```

`test.sh` は `external_tools/target/release/vis` でスコア算出、コンパクトテーブル + summary 出力。

## I.cc の重み（チューニング済）

```cpp
// plan_disp 内
score += chunk * 100000;
if (m != target_r) score += 50000;
if (nc) score += 100000;
if (Sd[k].empty()) score += 30000;     // ← Tuned (was 1000)
else score -= Sd[k].size() * 10;
score += min_id_bonus;
if (k in same half) score += 20000;
if (m in same half) score += 30000;    // ← Tuned (was 5000)
score += run * 150000;                 // ← Tuned chain bonus (was 40000)
score += rand_noise(NOISE);

// run_solver の build 順 cost
long long cost = d * 1000;             // ← Tuned: L * 100 を削除
cost += rand_noise(NOISE * 5);

// noise cycling
NOISE = (trials & 1) ? 5000 : 1000;
```

## 失敗試行の記録（重複しないように）

- chain extension のランダム停止: -1
- displace の chunk size ランダム分割: -6
- 2-step lookahead in D.cc: deterministic で +4 だが、ランダム再試行が減るので F.cc/I.cc に統合は要検討（未実装）
- 修正 dump (Sd[0..4] のみに分配): forward-only でも -3 (G.cc)
- 0/9 両側構築 (G.cc REV_LO=5): correctness 詰む

## サクセス基準

- I.cc 4913 を **超える** ことを目標
- 100 seeds で fails=0
- 1 seed 1.85s 以内
