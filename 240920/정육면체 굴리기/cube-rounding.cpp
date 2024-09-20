#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int N, M, X, Y, K;
int map[21][21];
int cmd[1001];
int dice[4][4];
int dy[5] = { 0, 0, 0, -1, 1 };
int dx[5] = { 0, 1, -1, 0, 0 };

void input() {

	cin >> N >> M >> Y >> X >> K;

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

	for (int i = 0; i < K; i++) {

		int nx = X + dx[cmd[i]];
		int ny = Y + dy[cmd[i]];

		if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;

		int temp = 0;

		if (map[ny][nx] == 0) {

			if (cmd[i] == 1) {
				map[ny][nx] = dice[1][2];
				temp = dice[1][0];
				dice[1][0] = dice[1][1];
				dice[1][1] = map[ny][nx];
				dice[1][2] = dice[1][3];
				dice[1][3] = temp;
				dice[3][1] = dice[1][3];
			}
			else if (cmd[i] == 2) {
				map[ny][nx] = dice[1][0];
				temp = dice[1][3];
				dice[1][3] = dice[1][2];
				dice[1][2] = dice[1][1];
				dice[1][1] = map[ny][nx];
				dice[1][0] = temp;
				dice[3][1] = dice[1][3];
			}
			else if (cmd[i] == 3) {
				map[ny][nx] = dice[0][1];
				temp = dice[3][1];
				dice[3][1] = dice[2][1];
				dice[2][1] = dice[1][1];
				dice[1][1] = map[ny][nx];
				dice[0][1] = temp;
				dice[1][3] = dice[3][1];
			}
			else if (cmd[i] == 4) {
				map[ny][nx] = dice[2][1];
				temp = dice[0][1];
				dice[0][1] = dice[1][1];
				dice[1][1] = map[ny][nx];
				dice[2][1] = dice[3][1];
				dice[3][1] = temp;
				dice[1][3] = dice[3][1];
			}

		}
		else {

			if (cmd[i] == 1) {
				temp = dice[1][0];
				dice[1][0] = dice[1][1];
				dice[1][1] = map[ny][nx];
				map[ny][nx] = 0;
				dice[1][2] = dice[1][3];
				dice[1][3] = temp;
				dice[3][1] = dice[1][3];
			}
			else if (cmd[i] == 2) {
				temp = dice[1][3];
				dice[1][3] = dice[1][2];
				dice[1][2] = dice[1][1];
				dice[1][1] = map[ny][nx];
				map[ny][nx] = 0;
				dice[1][0] = temp;
				dice[3][1] = dice[1][3];
			}
			else if (cmd[i] == 3) {
				temp = dice[3][1];
				dice[3][1] = dice[2][1];
				dice[2][1] = dice[1][1];
				dice[1][1] = map[ny][nx];
				map[ny][nx] = 0;
				dice[0][1] = temp;
				dice[1][3] = dice[3][1];
			}
			else if (cmd[i] == 4) {
				temp = dice[0][1];
				dice[0][1] = dice[1][1];
				dice[1][1] = map[ny][nx];
				map[ny][nx] = 0;
				dice[2][1] = dice[3][1];
				dice[3][1] = temp;
				dice[1][3] = dice[3][1];
			}

		}

		X = nx;
		Y = ny;

		cout << dice[3][1] << "\n";
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	//freopen("sample.txt", "r", stdin);

	input();
	solve();

	return 0;
}