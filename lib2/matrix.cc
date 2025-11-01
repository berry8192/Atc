// Matrix 行列演算 行列積 逆行列 行列式 O(N^3)

#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
using namespace std;

// ========== ライブラリ部分 ==========

// 行列クラス
template<typename T>
class Matrix {
private:
    vector<vector<T>> data;
    int rows, cols;

public:
    // コンストラクタ
    Matrix() : rows(0), cols(0) {}

    Matrix(int r, int c, T val = T()) : rows(r), cols(c) {
        data.assign(r, vector<T>(c, val));
    }

    Matrix(const vector<vector<T>>& mat) : data(mat) {
        rows = mat.size();
        cols = rows > 0 ? mat[0].size() : 0;
    }

    // アクセサ
    vector<T>& operator[](int i) { return data[i]; }
    const vector<T>& operator[](int i) const { return data[i]; }

    int get_rows() const { return rows; }
    int get_cols() const { return cols; }

    // 基本演算
    Matrix operator+(const Matrix& other) const {
        assert(rows == other.rows && cols == other.cols);
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = data[i][j] + other[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        assert(rows == other.rows && cols == other.cols);
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = data[i][j] - other[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        assert(cols == other.rows);
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result[i][j] += data[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator*(T scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    // 単位行列を生成
    static Matrix identity(int n) {
        Matrix result(n, n);
        for (int i = 0; i < n; i++) {
            result[i][i] = 1;
        }
        return result;
    }

    // 転置行列
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[j][i] = data[i][j];
            }
        }
        return result;
    }

    // 行列式（ガウス消去法）
    T determinant() const {
        assert(rows == cols);
        Matrix temp = *this;
        T det = 1;

        for (int i = 0; i < rows; i++) {
            // ピボット選択
            int pivot = i;
            for (int j = i + 1; j < rows; j++) {
                if (abs(temp[j][i]) > abs(temp[pivot][i])) {
                    pivot = j;
                }
            }

            if (pivot != i) {
                swap(temp[i], temp[pivot]);
                det *= -1;
            }

            if (temp[i][i] == T()) return T();

            det *= temp[i][i];

            // 消去
            for (int j = i + 1; j < rows; j++) {
                T factor = temp[j][i] / temp[i][i];
                for (int k = i; k < cols; k++) {
                    temp[j][k] -= factor * temp[i][k];
                }
            }
        }

        return det;
    }

    // ガウス・ジョーダン法による逆行列
    Matrix inverse() const {
        assert(rows == cols);
        Matrix aug(rows, cols * 2);

        // 拡大行列を作成 [A|I]
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                aug[i][j] = data[i][j];
            }
            aug[i][i + cols] = 1;
        }

        // ガウス・ジョーダン法
        for (int i = 0; i < rows; i++) {
            // ピボット選択
            int pivot = i;
            for (int j = i + 1; j < rows; j++) {
                if (abs(aug[j][i]) > abs(aug[pivot][i])) {
                    pivot = j;
                }
            }

            if (pivot != i) {
                swap(aug[i], aug[pivot]);
            }

            if (aug[i][i] == T()) {
                throw runtime_error("Matrix is not invertible");
            }

            // 対角要素を1にする
            T pivot_val = aug[i][i];
            for (int j = 0; j < cols * 2; j++) {
                aug[i][j] /= pivot_val;
            }

            // 他の行を消去
            for (int j = 0; j < rows; j++) {
                if (i != j) {
                    T factor = aug[j][i];
                    for (int k = 0; k < cols * 2; k++) {
                        aug[j][k] -= factor * aug[i][k];
                    }
                }
            }
        }

        // 右半分を取り出す
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = aug[i][j + cols];
            }
        }

        return result;
    }

    // 行列の累乗（高速化）
    Matrix power(long long n) const {
        assert(rows == cols);
        Matrix result = identity(rows);
        Matrix base = *this;

        while (n > 0) {
            if (n & 1) {
                result = result * base;
            }
            base = base * base;
            n >>= 1;
        }

        return result;
    }

    // 連立方程式を解く（ガウス消去法）
    vector<T> solve(const vector<T>& b) const {
        assert(rows == cols && (int)b.size() == rows);
        Matrix aug(rows, cols + 1);

        // 拡大行列を作成 [A|b]
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                aug[i][j] = data[i][j];
            }
            aug[i][cols] = b[i];
        }

        // 前進消去
        for (int i = 0; i < rows; i++) {
            // ピボット選択
            int pivot = i;
            for (int j = i + 1; j < rows; j++) {
                if (abs(aug[j][i]) > abs(aug[pivot][i])) {
                    pivot = j;
                }
            }

            if (pivot != i) {
                swap(aug[i], aug[pivot]);
            }

            if (aug[i][i] == T()) {
                throw runtime_error("No unique solution");
            }

            // 消去
            for (int j = i + 1; j < rows; j++) {
                T factor = aug[j][i] / aug[i][i];
                for (int k = i; k <= cols; k++) {
                    aug[j][k] -= factor * aug[i][k];
                }
            }
        }

        // 後退代入
        vector<T> x(rows);
        for (int i = rows - 1; i >= 0; i--) {
            x[i] = aug[i][cols];
            for (int j = i + 1; j < cols; j++) {
                x[i] -= aug[i][j] * x[j];
            }
            x[i] /= aug[i][i];
        }

        return x;
    }

    // 表示
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << setw(8) << fixed << setprecision(3) << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Mod演算用の行列クラス
template<int MOD>
class ModMatrix {
private:
    vector<vector<long long>> data;
    int rows, cols;

    long long mod(long long x) const {
        return ((x % MOD) + MOD) % MOD;
    }

    long long mod_pow(long long base, long long exp) const {
        long long result = 1;
        while (exp > 0) {
            if (exp & 1) result = mod(result * base);
            base = mod(base * base);
            exp >>= 1;
        }
        return result;
    }

    long long mod_inv(long long a) const {
        return mod_pow(a, MOD - 2);  // MODが素数の場合
    }

public:
    ModMatrix(int r, int c, long long val = 0) : rows(r), cols(c) {
        data.assign(r, vector<long long>(c, mod(val)));
    }

    ModMatrix(const vector<vector<long long>>& mat) : data(mat), rows(mat.size()) {
        cols = rows > 0 ? mat[0].size() : 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = mod(data[i][j]);
            }
        }
    }

    vector<long long>& operator[](int i) { return data[i]; }
    const vector<long long>& operator[](int i) const { return data[i]; }

    ModMatrix operator*(const ModMatrix& other) const {
        assert(cols == other.rows);
        ModMatrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result[i][j] = mod(result[i][j] + mod(data[i][k] * other[k][j]));
                }
            }
        }
        return result;
    }

    ModMatrix power(long long n) const {
        assert(rows == cols);
        ModMatrix result(rows, cols);
        for (int i = 0; i < rows; i++) result[i][i] = 1;

        ModMatrix base = *this;
        while (n > 0) {
            if (n & 1) result = result * base;
            base = base * base;
            n >>= 1;
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な行列演算
    cout << "例1: 基本的な行列演算" << endl;
    Matrix<double> A({{1, 2}, {3, 4}});
    Matrix<double> B({{5, 6}, {7, 8}});

    cout << "行列A:" << endl;
    A.print();
    cout << "行列B:" << endl;
    B.print();

    auto C = A * B;
    cout << "A * B:" << endl;
    C.print();
    cout << endl;

    // 例2: 行列式と逆行列
    cout << "例2: 行列式と逆行列" << endl;
    Matrix<double> D({{2, 1}, {1, 1}});
    cout << "行列D:" << endl;
    D.print();
    cout << "行列式: " << D.determinant() << endl;

    try {
        auto D_inv = D.inverse();
        cout << "逆行列:" << endl;
        D_inv.print();

        auto I = D * D_inv;
        cout << "D * D^(-1) (単位行列のはず):" << endl;
        I.print();
    } catch (const exception& e) {
        cout << "エラー: " << e.what() << endl;
    }
    cout << endl;

    // 例3: 連立方程式
    cout << "例3: 連立方程式 Ax = b" << endl;
    Matrix<double> A3({{2, 1}, {1, 3}});
    vector<double> b = {5, 7};

    cout << "係数行列A:" << endl;
    A3.print();
    cout << "右辺ベクトルb: ";
    for (double x : b) cout << x << " ";
    cout << endl;

    try {
        auto solution = A3.solve(b);
        cout << "解: ";
        for (double x : solution) cout << x << " ";
        cout << endl;
    } catch (const exception& e) {
        cout << "エラー: " << e.what() << endl;
    }
    cout << endl;

    // 例4: 行列の累乗
    cout << "例4: 行列の累乗" << endl;
    Matrix<long long> fib_matrix({{1, 1}, {1, 0}});
    cout << "フィボナッチ行列:" << endl;
    fib_matrix.print();

    auto fib10 = fib_matrix.power(10);
    cout << "10乗:" << endl;
    fib10.print();
    cout << "F(11) = " << fib10[0][1] << endl;  // フィボナッチ数列の11番目
    cout << endl;

    // 例5: Mod演算付き行列
    cout << "例5: Mod演算付き行列" << endl;
    const int MOD = 1000000007;
    ModMatrix<MOD> mod_fib({{1, 1}, {1, 0}});

    cout << "フィボナッチ行列 (mod " << MOD << "):" << endl;
    mod_fib.print();

    auto mod_fib_large = mod_fib.power(1000000);
    cout << "10^6乗 (mod " << MOD << "):" << endl;
    mod_fib_large.print();
    cout << endl;

    // 例6: 大きな行列の演算
    cout << "例6: 大きな行列の演算" << endl;
    int n = 3;
    Matrix<double> large_A(n, n);
    Matrix<double> large_B(n, n);

    // ランダムな値で初期化
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            large_A[i][j] = (i + 1) * (j + 1);
            large_B[i][j] = (i + j + 1);
        }
    }

    cout << "行列A:" << endl;
    large_A.print();
    cout << "行列B:" << endl;
    large_B.print();

    auto large_C = large_A * large_B;
    cout << "A * B:" << endl;
    large_C.print();

    cout << "det(A) = " << large_A.determinant() << endl;

    return 0;
}