#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int map[201][201];
int vis[201][201];

int mmax;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			cin >> map[i][j];
		}
	}
}

void dfs(int level, int y, int x, int sum) {

	if (level == 4) {
		if (sum > mmax) {
			mmax = sum;
		}
		return;
	}

	int nx = 0;
	int ny = 0;

	for (int i = 0; i < 4; i++){

		nx = x + dx[i];
		ny = y + dy[i];

		if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
		if (vis[ny][nx] == 1) continue;

		int s = sum + map[ny][nx];

		vis[ny][nx] = 1;
		dfs(level + 1, ny, nx, s);
		vis[ny][nx] = 0;
	}
}

void solve() {

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			vis[i][j] = 1;
			dfs(1, i, j, map[i][j]);
			vis[i][j] = 0;

			for (int k = 0; k < 4; k++){

				int sum = map[i][j];

				for (int l = 0; l < 3; l++){

					int ny = i + dy[(k + l) % 4];
					int nx = j + dx[(k + l) % 4];

					if (nx < 0 || ny < 0 || nx >= M || ny >= N) break;

					sum += map[ny][nx];
				}

				if (sum > mmax) {
					mmax = sum;
				}

			}
		}
	}

	cout << mmax;
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