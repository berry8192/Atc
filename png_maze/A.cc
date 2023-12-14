#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <bits/stdc++.h>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int imax=2147483647;

auto seed=1;
mt19937 mt(seed);

int dh[]={1, 0, -1, 0};
int dw[]={0, 1, 0, -1};
void solve(vector<vector<int>> &vec, int width, int height){
	vector<vector<int>> dis(height, vector<int>(width, imax));
	queue<int> qh, qw;

	qh.push(1);
	qw.push(1);
	dis[1][1]=0;
	while (!qh.empty()) { // 時間の許す限り回す
        int ch=qh.front();
        int cw=qw.front();
    	qh.pop();
    	qw.pop();
		for(int i=0;i<4;i++){
			int nh=ch+dh[i];
			int nw=cw+dw[i];
			if(nh<0 || height-1<nh) continue;
			if(nw<0 || width-1<nw) continue;
			if(vec[nh][nw]==1) continue;
			if(dis[nh][nw]<=dis[ch][cw]+1) continue;
			dis[nh][nw]=dis[ch][cw]+1;
			qh.push(nh);
			qw.push(nw);
		}
	}
	// cout<< "root: " << dis[height-2][width-2] <<endl;

	int ch=height-2;
	int cw=width-2;
	int cd=dis[ch][cw];
	while(dis[ch][cw]!=0){
		for(int i=0;i<4;i++){
			if(dis[ch+dh[i]][cw+dw[i]]==dis[ch][cw]-1){
				vec[ch+dh[i]][cw+dw[i]]=2;
				ch+=dh[i];
				cw+=dw[i];
				cd--;
				break;
			}
		}
	}
	vec[height-2][width-2]=2;
}

void add_edge(vector<vector<int>> &vec, dsu &d, int idx, int width, int height, bool edge){
	int y=idx/width;
	int x=idx%width;
	int u, v;
	if(y%2==1 && x%2==0){
		// 縦の辺
		u=(y-1)*width+x;
		v=(y+1)*width+x;
		if(y>=height) return;
	}else if(y%2==0 && x%2==1){
		// 横の辺
		u=y*width+x-1;
		v=y*width+x+1;
		if(u<0) return;
	}else{
		return;
	}
	if(!edge && d.same(u, v)) return;
	vec[y][x]=1;
	d.merge(u, v);
}

void gen_maze(vector<vector<int>> &vec, int width, int height){
	vector<int> perm;
	for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
			if(y%2==0 && x%2==0){
				vec[y][x]=1;
				continue;
			}else if(y%2==1 && x%2==1){
				vec[y][x]=0;
				continue;
			}
			perm.push_back(y*width+x);
		}
	}
	shuffle(perm.begin(), perm.end(), mt);

	dsu d(width*height);

	for (int y = 0; y < height; y++){
		// cout<< y <<endl;
		int x=0;
		add_edge(vec, d, y*width+x, width, height, true);
		x=width-1;
		add_edge(vec, d, y*width+x, width, height, true);
	}
	for (int x = 0; x < width; x++){
		// cout<< x <<endl;
		int y=0;
		add_edge(vec, d, y*width+x, width, height, true);
		y=height-1;
		add_edge(vec, d, y*width+x, width, height, true);
	}

	for(int i=0;i<perm.size();i++){
		add_edge(vec, d, perm[i], width, height, false);
	}
}

void createColoredNoiseImage(const char* filename, const char* filename_ans, int width, int height, int zoom) {
    // Allocate memory for image data
    unsigned char* image = (unsigned char*)malloc(width * height * zoom * zoom * 3);  // 3 channels (RGB)
    unsigned char* image_ans = (unsigned char*)malloc(width * height * zoom * zoom * 3);  // 3 channels (RGB)

	vector<vector<int>> v(height, vector<int>(width));
	vector<vector<int>> v_ans(height, vector<int>(width));
	gen_maze(v, width, height);
	gen_maze(v_ans, width, height);

    // Generate colored noise
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Calculate the index for the current pixel
			for(int i=0;i<zoom;i++){
				for(int j=0;j<zoom;j++){
					int index = ((y*zoom+i)*width*zoom+x*zoom+j) * 3;
					// white
					image[index]     = 255;  // Red
					image[index + 1] = 255;  // Green
					image[index + 2] = 255;  // Blue
					// Assign random values to RGB channels
					if(v[y][x]==1) image[index]     = 0;  // Red
					if(v[y][x]>=1) image[index + 1] = 0;  // Green
					if(v[y][x]>=1) image[index + 2] = 0;  // Blue
				}
			}
        }
    }
    stbi_write_png(filename, width * zoom, height * zoom, 3, image, width * zoom * 3);

	solve(v_ans, width, height);

	
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Calculate the index for the current pixel
			for(int i=0;i<zoom;i++){
				for(int j=0;j<zoom;j++){
					int index = ((y*zoom+i)*width*zoom+x*zoom+j) * 3;
					// white
					image[index]     = 255;  // Red
					image[index + 1] = 255;  // Green
					image[index + 2] = 255;  // Blue
					// Assign random values to RGB channels
					if(v_ans[y][x]==1) image[index]     = 0;  // Red
					if(v_ans[y][x]>=1) image[index + 1] = 0;  // Green
					if(v_ans[y][x]>=1) image[index + 2] = 0;  // Blue
				}
			}
        }
    }

    // Save the image to a file
    stbi_write_png(filename_ans, width * zoom, height * zoom, 3, image, width * zoom * 3);

    // Free allocated memory
    free(image);
}

int main() {
    const char* filename = "maze.png";
    const char* filename_ans = "maze_ans.png";
    int width = 3840;
    int height = 2160;
	int zoom = 1;
	// cin>> width >> height >> zoom;
	cin>> seed;
	assert(0<width*zoom && width*zoom<=3841);
	assert(0<height*zoom && height*zoom<=3841);

    createColoredNoiseImage(filename, filename_ans, width+1, height+1, zoom);

    return 0;
}
