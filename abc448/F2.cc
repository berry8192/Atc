#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

struct Timer {
    chrono::_V2::system_clock::time_point start;

    Timer() { start = chrono::system_clock::now(); }
    double progress() {
        chrono::_V2::system_clock::time_point current =
            chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(current - start)
                   .count() /
               1900.0;
    }
};
Timer timer;

int seed = 1;
mt19937 mt(seed);

class Point {
  public:
    int x, y;

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    Point() {
        this->x = 0;
        this->y = 0;
    }

    // 二点間の距離を計算
    inline int dist(const Point &other) const {
        int diffx = abs(x - other.x);
        int diffy = abs(y - other.y);
        return diffx + diffy;
    }
};

// 経路全体の距離を計算
long long pathLength(vector<Point> &path) {
    int n = path.size();
    long long length = path[n - 1].dist(path[0]);
    for (int i = 0; i < n - 1; i++) {
        length += path[i].dist(path[i + 1]);
    }
    return length;
}

// path[i]->path[i+1] と path[j]->path[j+1] の二辺を
// それぞれ path[i]->path[j] と path[i+1]->path[j+1] で置き換える。
void swap_edges(vector<Point> &path, int i, int j) {
    i += 1;
    while (i < j) {
        Point temp = path[i];
        path[i] = path[j];
        path[j] = temp;
        i++;
        j--;
    }
}

// 経路を出力
void printPath(string pathName, vector<Point> &path) {
    printf("%s = [", pathName.c_str());
    for (int i = 0; i < path.size(); i++) {
        if (i % 10 == 0) {
            printf("\n  ");
        }
        if (i < path.size() - 1) {
            printf("[%.1f, %.1f], ", path[i].x, path[i].y);
        } else {
            printf("[%.1f, %.1f]", path[i].x, path[i].y);
        }
    }
    printf("\n];\n");
}

// ノード数nのランダムな経路を作る。各ノードの座標はx,yともに0以上1000以下。
vector<Point> createRandomPath(int n) {
    vector<Point> path;
    for (int i = 0; i < n; i++) {
        int x = (int)rand() / (int)(RAND_MAX / 1000);
        int y = (int)rand() / (int)(RAND_MAX / 1000);
        path.push_back(Point(x, y));
    }
    return path;
}

int main() {
    int nn;
    cin >> nn;
    map<pair<int, int>, int> mp;
    int x, y;
    vector<Point> path;
    for (int i = 0; i < nn; i++) {
        cin >> x >> y;
        mp[{x, y}] = i + 1;
        path.push_back(Point(x, y));
    }

    // printPath("path1", path);
    long long curLength = pathLength(path);
    // printf("path1len = %d;\n\n", curLength);

    int n = path.size();
    while (timer.progress() < 1) {
        int i = mt() % (n - 2) + 1;
        int j = mt() % (n - i) + i + 1;
        if (j - i <= 1 || j == n - 1)
            continue;
        long long lengthDelta =
            -path[i].dist(path[i + 1]) - path[j].dist(path[(j + 1) % n]) +
            path[i].dist(path[j]) + path[i + 1].dist(path[(j + 1) % n]);

        // もし経路の長さが短くなったのならば、実際に2-optを行い辺を交換する
        if (lengthDelta < 0) {
            swap_edges(path, i, j);
            curLength += lengthDelta;
            if (curLength < 10000000000LL) {
                cerr << curLength << endl;
                break;
            }
        }
    }

    // printPath("path2", path);
    // printf("path2len = %d;\n", curLength);

    for (int i = 0; i < nn; i++) {
        cout << mp[{path[i].x, path[i].y}] << " ";
    }
    cout << endl;
    return 0;
}