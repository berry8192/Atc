問題文
=====
A君はソフトウェアテストのテストを行います。テスト対象の機能には$N$個のパラメータがあり、$i$番目のパラメータは$P_i$通りの値を持つことができます。

テストでは全てのパラメータのパターンを試す必要がありますが、A君が試すことになるテストケースはいくつになるでしょうか？

答えは非常に大きくなる可能性があるため、$10^9+7$で割ったあまりを答えてください。

制約
-----
- 入力はすべて整数である。
- $1 \leq N \leq 10^5$
- $1 \leq P_i \leq 10^9$

入力
-----
入力は以下の形式で標準入力から与えられる。
```md:
$N$

$P_1$ $P_2$ ... $P_N$
```

出力
-----
A君が行うことになるテストケースの個数を出力せよ。


サンプル
-----
```入力例1
2
3 4

```

```出力例1
12

```
1つめのパラメータが3通り、2つめのパラメータが4通りあるので$3 \times 4=12$ 通りが答えです。

-----
```入力例2
1
100

```

```出力例2
100

```
-----
```入力例3
4
1000000000 1000000000 1000000000 1000000000

```

```出力例3
2401

```
答えを $10^9+7$ で割ったあまりを出力してください。