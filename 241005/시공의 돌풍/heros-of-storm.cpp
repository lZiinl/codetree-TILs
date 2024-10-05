#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int N, M, T;
int map[52][52];
int up_y, down_y;
int plusmap[52][52];

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void input() {
	cin >> N >> M >> T;
	int cnt = 0;

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){
			cin >> map[i][j];
			if (map[i][j] == -1) {
				if (cnt == 0){
					up_y = i;
					cnt++;
				}
				else {
					down_y = i;
				}
			}
		}
	}
}

void dup() {
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){
			if (map[i][j] == -1) continue;

			int new_d = map[i][j] / 5;
			int cnt = 0;

			for (int k = 0; k < 4; k++){

				int nx = j + dx[k];
				int ny = i + dy[k];

				if (nx < 1 || ny < 1 || nx > M || ny > N) continue;
				if (map[ny][nx] == -1) continue;

				cnt++;
				plusmap[ny][nx] += new_d;
			}
			map[i][j] -= new_d * cnt;
		}
	}
}

void add() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			map[i][j] += plusmap[i][j];
			plusmap[i][j] = 0;
		}
	}
}

void up_move() {
	for (int i = up_y-1; i > 0; i--){
		map[i][1] = map[i - 1][1];
	}
	for (int i = 1; i < M; i++){
		map[1][i] = map[1][i + 1];
	}
	for (int i = 1; i < up_y; i++){
		map[i][M] = map[i + 1][M];
	}
	for (int i = M; i > 1; i--){
		map[up_y][i] = map[up_y][i - 1];
	}
	map[up_y][2] = 0;
}

void down_move() {
	for (int i = down_y+1; i < N; i++){
		map[i][1] = map[i + 1][1];
	}
	for (int i = 1; i < M; i++){
		map[N][i] = map[N][i + 1];
	}
	for (int i = N; i > down_y; i--){
		map[i][M] = map[i - 1][M];
	}
	for (int i = M; i > 1; i--){
		map[down_y][i] = map[down_y][i - 1];
	}
	map[down_y][2] = 0;
}

void move() {
	up_move();
	down_move();
}

void print() {
	int result = 0;

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){
			if (map[i][j] != -1) {
				result += map[i][j];
			}
		}
	}
	cout << result;
}

void solve() {

	for (int i = 0; i < T; i++){
		dup();
		add();
		move();
	}
	print();
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	solve();

	return 0;
}