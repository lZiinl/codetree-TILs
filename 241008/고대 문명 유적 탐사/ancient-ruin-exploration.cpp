#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<queue>
#include<cstring>

using namespace std;

int K, M;
int map[5][5];
queue<int>q;
int flag; //탐사 종료 확인

void input() {
	cin >> K >> M;

	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < M; i++){
		int temp;
		cin >> temp;
		q.push(temp);
	}
}

int s_map[3][3];

void sel_map(int y, int x) {

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			s_map[i][j] = map[y + i][x + j];
		}
	}
}

int c_map[5][5];

void copymap() {
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			c_map[i][j] = map[i][j];
		}
	}
}

void rotate() {

	int temp = s_map[0][2];
	s_map[0][2] = s_map[0][0];
	s_map[0][0] = s_map[2][0];
	s_map[2][0] = s_map[2][2];
	s_map[2][2] = temp;

	temp = s_map[0][1];
	s_map[0][1] = s_map[1][0];
	s_map[1][0] = s_map[2][1];
	s_map[2][1] = s_map[1][2];
	s_map[1][2] = temp;

}

void paste(int y, int x) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			c_map[y + i][x + j] = s_map[i][j];
		}
	}
}

int vismap[5][5];
struct Node {
	int y, x, s;
};

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int mmax;
int result;
int tx, ty;

int r_map[5][5];

void resultmap() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			r_map[i][j] = c_map[i][j];
		}
	}
}

int r_time;

void bfs1(int r) {

	int sum = 0;

	memset(vismap, 0, sizeof(vismap));
	for (int j = 0; j < 5; j++){
		for (int i = 0; i < 5; i++){

			if (vismap[i][j] != 0) continue;
			
			queue<Node>bq;
			bq.push({ i,j });
			vismap[i][j] = 1;
			
			int cnt = 0;

			while (!bq.empty()) {

				Node now = bq.front();
				bq.pop();
				cnt++;

				for (int k = 0; k < 4; k++){

					int nx = now.x + dx[k];
					int ny = now.y + dy[k];

					if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5) continue;
					if (vismap[ny][nx] == 1) continue;
					if (c_map[now.y][now.x] != c_map[ny][nx]) continue;
					vismap[ny][nx] = 1;

					bq.push({ ny, nx });
				}
			}

			if (cnt >= 3) {
				sum += cnt;
				flag = 0;
			}
		}
	}

	if (sum >= mmax) {
		if (r < r_time) {
			mmax = sum;
			resultmap();
		}
	}
}

int flag2;

void bfs2() {
	memset(vismap, 0, sizeof(vismap));
	flag2 = 1;

	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			if (vismap[i][j] == 1)continue;

			queue<Node>bq;
			vector<Node>v;
			bq.push({ i,j });
			v.push_back({ i,j });
			vismap[i][j] = 1;

			int cnt = 0;

			while (!bq.empty()) {

				Node now = bq.front();
				bq.pop();
				cnt++;

				for (int k = 0; k < 4; k++){

					int nx = now.x + dx[k];
					int ny = now.y + dy[k];

					if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5) continue;
					if (vismap[ny][nx] == 1) continue;
					if (r_map[now.y][now.x] != r_map[ny][nx]) continue;
					vismap[ny][nx] = 1;

					bq.push({ ny,nx });
					v.push_back({ ny,nx });
				}
			}

			if (cnt >= 3) {
				for (int i = 0; i < v.size(); i++) {
					result++;
					r_map[v[i].y][v[i].x] = 0;
					flag2 = 0;
				}
			}
		}
	}
}

void m_insert() {
	for (int j = 0; j < 5; j++){
		for (int i = 4; i >= 0; i--){
			if (r_map[i][j] == 0) {
				r_map[i][j] = q.front();
				q.pop();
			}
		}
	}
}

void solve() {

	copymap();

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){

			sel_map(i, j);

			for (int k = 0; k < 4; k++){
				rotate();
				paste(i,j);

				bfs1(k);
			}
		}
	}

	if (flag == 1) return;

	while (flag2 == 0) {
		bfs2();
		m_insert();
	}
	
}

void ccp() {
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			map[i][j] = r_map[i][j];
		}
	}
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	
	for (int i = 0; i < K; i++){
		r_time = 10;
		mmax = 0;
		flag = 1;
		flag2 = 0;
		result = 0;

		solve();
		if (flag == 1) break;
		cout << result << " ";
		ccp();
	}


	return 0;
}