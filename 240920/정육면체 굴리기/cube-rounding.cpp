#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int N, M, K;
int sp_x, sp_y;
int map[21][21];
int cmd[1001];
int dy[4] = { 1, 0, 0, -1 };
int dx[4] = { 0, 1, -1, 0 };
int dice[4][4];

void input() {
	cin >> N >> M >> sp_y >> sp_x >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < K; i++) {
		cin >> cmd[i];
	}
}

void solve() {

	int y = sp_y;
	int x = sp_x;

	for (int i = 0; i < K; i++) {
		int dir = (cmd[i] % 4);

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		//벽이면 가만히 있음
		if (nx < 0 || nx >= M || ny < 0 || ny >= N) {
			continue;
		}

		int temp = 0;

		//남쪽으로 움직이면
		if (dir == 0) {
			if (map[ny][nx] == 0) {
				map[ny][nx] = dice[2][1];
				temp = dice[0][1];
				dice[0][1] = dice[1][1];
				dice[1][1] = map[ny][nx];
				dice[2][1] = dice[3][1];
				dice[3][1] = temp;
				dice[1][3] = dice[3][1];
			}
			else {
				temp = dice[0][1];
				dice[0][1] = dice[1][1];
				dice[1][1] = map[ny][nx];
				map[ny][nx] = 0;
				dice[2][1] = dice[3][1];
				dice[3][1] = temp;
				dice[1][3] = dice[3][1];
			}
		}

		//동쪽
		if (dir == 1) {
			if (map[ny][nx] == 0) {
				map[ny][nx] = dice[1][2];
				temp = dice[1][0];
				dice[1][0] = dice[1][1];
				dice[1][1] = map[ny][nx];
				dice[1][2] = dice[1][3];
				dice[1][3] = temp;
				dice[3][1] = dice[1][3];
			}
			else {
				temp = dice[1][0];
				dice[1][0] = dice[1][1];
				dice[1][1] = map[ny][nx];
				map[ny][nx] = 0;
				dice[1][2] = dice[1][3];
				dice[1][3] = temp;
				dice[3][1] = dice[1][3];
			}
		}

		//서쪽
		if (dir == 2) {
			if (map[ny][nx] == 0) {
				map[ny][nx] = dice[1][0];
				temp = dice[1][3];
				dice[1][3] = dice[1][2];
				dice[1][2] = dice[1][1];
				dice[1][1] = map[ny][nx];
				dice[1][0] = temp;
				dice[3][1] = dice[1][3];
			}
			else {
				temp = dice[1][3];
				dice[1][3] = dice[1][2];
				dice[1][2] = dice[1][1];
				dice[1][1] = map[ny][nx];
				map[ny][nx] = 0;
				dice[1][0] = temp;
				dice[3][1] = dice[1][3];
			}
		}

		//북쪽
		if (dir == 3) {
			if (map[ny][nx] == 0) {
				map[ny][nx] = dice[0][1];
				temp = dice[3][1];
				dice[3][1] = dice[2][1];
				dice[2][1] = dice[1][1];
				dice[1][1] = map[ny][nx];
				dice[0][1] = temp;
				dice[1][3] = dice[3][1];
			}
			else {
				temp = dice[3][1];
				dice[3][1] = dice[2][1];
				dice[2][1] = dice[1][1];
				dice[1][1] = map[ny][nx];
				map[ny][nx] = 0;
				dice[0][1] = temp;
				dice[1][3] = dice[3][1];
			}
			
		}

		x = nx;
		y = ny;
		cout << dice[3][1] << "\n";
	}
}

int main() {
	//freopen("sample.txt", "r", stdin);

	input();

	solve();

	return 0;
}