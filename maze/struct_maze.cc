#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

int dh[]={1, 0, -1, 0};
int dw[]={0, 1, 0, -1};
string dir="DRUL";

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);
std::chrono::system_clock::time_point start, current;

struct Maze{
	int height, width, maze_path_length, maze_curve;
	vector<string> board;
	vector<vector<int>> dis;

	Maze(){};
	Maze(int h, int w, char fill_c='.'){
		height=h;
		width=w;
		string base;
		rep(i, width) base+=fill_c;
		board.resize(height, base);
		dis.resize(height, vector<int>(width, imax));
	}

	void make_enclosure(char wall_c='#'){
		rep(i, height){
			rep(j, width){
				if(i==0 || i==height-1 || j==0 || j==width-1) board[i][j]=wall_c;
			}
		}
	}
	void make_wall(double TIME_LIMIT=500, char wall_c='#'){
		//開始時間の計測
		start = chrono::system_clock::now();

		while (true) { // 時間の許す限り回す
			current = chrono::system_clock::now(); // 現在時刻
			if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;

			int start_h=(mt()%(height/2+1))*2;
			int start_w=(mt()%(width/2+1))*2;
			int cd=mt()%4;
			int lp=0;
			int search_h;
			int search_w;
			while(1){
				lp++;
				search_h=start_h+dh[cd]*lp;
				search_w=start_w+dw[cd]*lp;
				if(search_h<0 || height-1<search_h) break;
				if(search_w<0 || width-1<search_w) break;
				if(board[search_h][search_w]==wall_c) break;
			}
			if(lp<4) continue;
			lp/=2;
			lp--;
			lp=mt()%lp;
			lp++;
			lp*=2;
			// int goal_h=start_h+dh[cd]*lp;
			// int goal_w=start_w+dw[cd]*lp;

			if(board[start_h][start_w]!=wall_c) continue;
			// if(goal_h<0 || h-1<goal_h) continue;
			// if(goal_w<0 || w-1<goal_w) continue;
			// if(board[goal_h][goal_w]=='#') continue;
			rep3(i, lp+1, 1) board[start_h+dh[cd]*i][start_w+dw[cd]*i]=wall_c;
			// board[(goal_h+start_h)/2][(goal_w+start_w)/2]='#';
		}
	}
	void bfs(int start_h=1, int start_w=1){
		queue<int> qh, qw;
		qh.push(start_h);
		qw.push(start_w);
		dis[start_h][start_w]=0;
		while (!qh.empty()) { // 時間の許す限り回す
			int ch=qh.front();
			int cw=qw.front();
			qh.pop();
			qw.pop();
			rep(i, 4){
				int nh=ch+dh[i];
				int nw=cw+dw[i];
				if(nh<0 || height-1<nh) continue;
				if(nw<0 || width-1<nw) continue;
				if(board[nh][nw]=='#') continue;
				if(dis[nh][nw]<=dis[ch][cw]+1) continue;
				dis[nh][nw]=dis[ch][cw]+1;
				qh.push(nh);
				qw.push(nw);
			}
		}
	}
	int get_path_length(int goal_h, int goal_w){
		maze_path_length=dis[goal_h][goal_w];
		return maze_path_length;
	}
	void paint_answer(int goal_h, int goal_w, char goal_char='G'){
		int ch=goal_h;
		int cw=goal_w;
		int cd=dis[ch][cw];
		int curve=-1;
		char last_dir=-1;
		while(dis[ch][cw]!=0){
			rep(i, 4){
				if(dis[ch+dh[i]][cw+dw[i]]==dis[ch][cw]-1){
					board[ch+dh[i]][cw+dw[i]]=dir[(i+2)%4];
					if(board[ch+dh[i]][cw+dw[i]]!=board[ch][cw]){
						curve++;
						last_dir=board[ch][cw];
					}
					ch+=dh[i];
					cw+=dw[i];
					cd--;
					break;
				}
			}
		}
		board[goal_h][goal_w]='G';
		maze_curve=curve;
	}
	void make_maze(int start_h, int start_w, int goal_h, int goal_w){
		make_enclosure();
		make_wall();
		bfs(start_h, start_w);
		get_path_length(goal_h, goal_w);
		paint_answer(goal_h, goal_w);
	}

	void print_board(){
		rep(i, height) cout<< board[i] <<endl;
	}
};

int main(){

	int h, w, lp;
	cin>> h >> w >> lp;

	Maze best(h, w);
	best.make_maze(1, 1, h-2, w-2);
	rep(i, lp){
		Maze current(h, w);
		current.make_maze(1, 1, h-2, w-2);
		if(best.maze_path_length<current.maze_path_length){
			// cout<< "curve:" << current.maze_curve SP << "length:" << current.maze_path_length <<endl;
			// current.print_board();
			best=current;
		}
	}
	best.paint_answer(h-2, w-2);
	best.print_board();

	return 0;
}