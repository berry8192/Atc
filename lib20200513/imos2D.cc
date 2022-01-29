/* https://imoz.jp/algorithms/imos_method.html
いもす法では，矩形の左上 (A[i],C[i]) に +1 を，
右上 (A[i],D[i]) に −1 を，左下 (B[i],C[i]) に
 −1 を，右下 (B[i],D[i]) に +1 を加算し，
 答えを求める直前に累積和を求めます．記録には O(N) が，
 累積和の計算には O(WH) がかかるので，
 全体としての計算量は O(N+WH) となります．*/

for (int y = 0; y < H; y++) {
  for (int x = 0; x < W; x++) {
    tiles[y][x] = 0;
  }
}
// 重みの加算 (図 3)
for (int i = 0; i < N; i++) {
  tiles[C[i]][A[i]]++;
  tiles[C[i]][B[i]]--;
  tiles[D[i]][A[i]]--;
  tiles[D[i]][B[i]]++;
}
// 横方向への累積和 (図 4, 5)
for (int y = 0; y < H; y++) {
  for (int x = 1; x < W; x++) {
    tiles[y][x] += tiles[y][x - 1];
  }
}
// 縦方向の累積和 (図 6, 7)
for (int y = 1; y < H; y++) {
  for (int x = 0; x < W; x++) {
    tiles[y][x] += tiles[y - 1][x];
  }
}
// 最大値を調べる
int tile_max = 0;
for (int y = 0; y < H; y++) {
  for (int x = 0; x < W; x++) {
    if (tile_max < tiles[y][x]) {
      tile_max = tiles[y][x];
    }
  }
}