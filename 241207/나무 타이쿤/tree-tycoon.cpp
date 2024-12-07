#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int N, M;
int map[16][16];
int newmap[16][16];

int nut[16][16];
int new_nut[16][16];
int D, P;

void input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cin >> map[i][j];
		}
	}

	for (int i = N-2; i < N; i++){
		for (int j = 0; j < 2; j++){
			nut[i][j] = 1;
		}
	}

}

void move() {
	memset(new_nut, 0, sizeof(new_nut));

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){

			//영양제가 있으면 이동시키기
			if (nut[i][j] == 1) {
				int ny = ((i + dy[D - 1] * P) + N) % N;
				int nx = ((j + dx[D - 1] * P) + N) % N;

				new_nut[ny][nx] = 1;
			}
		}
	}
}

void grow() {
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			
			newmap[i][j] = map[i][j];

			if (new_nut[i][j] == 1) {

				newmap[i][j]++;

				for (int k = 1; k <= 4; k++){
					int ny = i + dy[2 * k - 1];
					int nx = j + dx[2 * k - 1];

					if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

					if (map[ny][nx] > 0) {
						newmap[i][j]++;
					}

					if (map[ny][nx] == 0 && new_nut[ny][nx] == 1) {
						newmap[i][j]++;
					}
				}
			}
		}
	}
}

void map_copy() {
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			map[i][j] = newmap[i][j];
		}
	}
}

void cut() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (new_nut[i][j] == 1) continue;

			if (map[i][j] >= 2) {
				map[i][j] -= 2;
				nut[i][j] = 1;
			}
		}
	}
}

void solve() {

	for (int i = 1; i <= M; i++){
		cin >> D >> P;
		move();
		memset(nut, 0, sizeof(nut));
		grow();
		map_copy();
		cut();
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(0);

	//freopen("sample.txt", "r", stdin);

	input();
	solve();

	int ans = 0;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			ans += map[i][j];
		}
	}

	cout << ans;

	return 0;
}