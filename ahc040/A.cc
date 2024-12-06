#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;
// using namespace atcoder;

// std::ofstream outputFile("log.csv");

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] << ", ";
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) cout << pvv[i] << ", ";
// 	// rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
// 	cout<< pvv[pvv.size()-1] <<endl;
// }

// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
//         // outputFile<< "i: " << i <<endl;
// 		rep(j, pvv[i].size()-1){
// 			outputFile<< pvv[i][j] << ", ";
// 		}
// 		if(pvv[i].size()) outputFile<< pvv[i][pvv[i].size()-1] <<endl;
// 	}
// }
// template <class T> void PM(T pm) {
//     // cout<< "{";
// 	for(auto m : pm){
// 		outputFile<< "(" << m.first << "->" << m.second << "), ";
// 	}
// 	// cout<< "}";
// 	outputFile<<endl;
// }

int imax = 2147483647;
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 1900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

struct Timer {
    chrono::_V2::system_clock::time_point start;

    Timer() { start = chrono::system_clock::now(); }
    double progress() {
        chrono::_V2::system_clock::time_point current =
            chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(current - start)
                   .count() /
               TIME_LIMIT;
    }
};
Timer timer;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

bool intersection(int l1, int r1, int l2, int r2) {
    return l2 <= r1 && l1 <= r2;
}

int N, T, sigma;
string direction_string = "UL";

// 構造体
struct Pos {
    int w;
    int h;

    Pos() {};
    Pos(int ww, int hh) {
        w = ww;
        h = hh;
    }

    void rotate() { swap(w, h); }
};

vector<Pos> initial_rectangles;

struct Rectangle {
    int parent;
    char direction;
    int rotate;
    int left;
    int top;
    int width;
    int height;

    Rectangle(int pa, char di, int ro, int le, int to, int wi, int he) {
        parent = pa;
        direction = di;
        rotate = ro;
        left = le;
        top = to;
        width = wi;
        height = he;
    }
};

struct Board {
    vector<Rectangle> rectangles;

    void add_rectangle(int index, int parent, int direction, int rotate) {
        // cerr << "add_rectangle()" << endl;
        // cerr << index SP << parent SP << direction SP << rotate SP <<
        // int(rectangles.size()) << endl; cerr << "initial_rectangles[index].w
        // = " << initial_rectangles[index].w << endl; cerr <<
        // "initial_rectangles[index].h = " << initial_rectangles[index].h <<
        // endl;
        assert(index <= int(rectangles.size()));
        assert(parent < index);
        assert(direction == 0 || direction == 1);
        assert(rotate == 0 || rotate == 1);
        char char_direction = direction_string[direction];
        Pos initial_rectangle = initial_rectangles[index];
        if (rotate) {
            initial_rectangle.rotate();
        }
        Pos top_left_pos =
            calc_top_left_pos(index, parent, char_direction, initial_rectangle);
        rectangles.emplace_back(parent, char_direction, rotate, top_left_pos.w,
                                top_left_pos.h, initial_rectangle.w,
                                initial_rectangle.h);
    }
    Pos calc_top_left_pos(int index, int parent, char direction,
                          Pos initial_rectangle) {
        // cerr << "calc_top_left_pos()" << endl;
        // cerr << index SP << parent SP << direction SP <<
        // int(rectangles.size()) << endl;
        assert(parent < int(rectangles.size()));
        assert(direction == 'U' || direction == 'L');
        Pos rtn;
        if (direction == 'U') {
            int left_pos, right_pos;
            if (parent == -1) {
                left_pos = 0;
            } else {
                left_pos = rectangles[parent].left;
            }
            right_pos = left_pos + initial_rectangle.w;
            rtn.w = left_pos;

            int max_bottom = 0;
            rep(i, rectangles.size()) {
                int left = rectangles[i].left;
                int right = left + initial_rectangles[i].w;
                if (intersection(left, right, left_pos, right_pos)) {
                    max_bottom = max(max_bottom, rectangles[i].top +
                                                     initial_rectangles[i].h);
                }
            }
            rtn.h = max_bottom;
        } else {
            int top_pos, bottom_pos;
            if (parent == -1) {
                top_pos = 0;
            } else {
                top_pos = rectangles[parent].top;
            }
            bottom_pos = top_pos + initial_rectangles[index].h;
            rtn.h = top_pos;

            int max_right = 0;
            rep(i, rectangles.size()) {
                int top = rectangles[i].top;
                int bottom = top + initial_rectangle.h;
                if (intersection(top, bottom, top_pos, bottom_pos)) {
                    max_right = max(max_right, rectangles[i].left +
                                                   initial_rectangles[i].w);
                }
            }
            rtn.w = max_right;
        }
        return rtn;
    }
    int evaluate() {
        int width = 0;
        int height = 0;
        rep(i, N) {
            width = max(width, rectangles[i].left + initial_rectangles[i].w);
            height = max(height, rectangles[i].top + initial_rectangles[i].h);
        }
        return width + height;
    }
    void preview_rectangles() {
        // cerr << "preview_rectangles()" << endl;
        rep(i, N) {
            cerr << i SP << rectangles[i].parent SP
                 << rectangles[i].direction SP << rectangles[i].rotate SP
                 << rectangles[i].left SP << rectangles[i].top SP
                 << rectangles[i].width SP << rectangles[i].height << endl;
        }
    }
    Pos output() {
        cout << N << endl;
        rep(i, N) {
            cout << i SP << rectangles[i].rotate SP
                 << rectangles[i].direction SP << rectangles[i].parent << endl;
        }
        int W, H;
        cin >> W >> H;
        return Pos(W, H);
    }
};

void inpt() {
    // cerr << "inpt()" << endl;
    cin >> N >> T >> sigma;
    int ih, iw;
    rep(i, N) {
        cin >> ih >> iw;
        initial_rectangles.emplace_back(ih, iw);
    }
}

int main() {
    inpt();

    vector<Board> best_boards(N + 1);
    vector<int> best_scores(N + 1, imax);
    rep(index, N) {
        rep3(parent, index, -1) {
            rep(direction, 2) {
                rep(rotate, 2) {
                    Board board = best_boards[index];
                    board.add_rectangle(index, parent, direction, rotate);
                    int score = board.evaluate();
                    if (score < best_scores[index + 1]) {
                        // cerr << index SP << score << endl;
                        best_scores[index + 1] = score;
                        best_boards[index + 1] = board;
                    }
                }
            }
        }
    }
    // best_boards[N].preview_rectangles();
    rep(i, T) { best_boards[N].output(); }

    return 0;
}
