#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

int N;
int map[21][21];
int mmax;

//방향 상우하좌
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

void input() {
	cin >> N;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cin >> map[i][j];
		}
	}
}

void umove() {

	int check_map[21][21] = {};

	for (int j = 0; j < N; j++){
		for (int i = 0; i < N; i++){
			if (map[i][j] == 0) continue;

			int x = j;
			int y = i;

			while (1) {
				int nx = x + dx[0];
				int ny = y + dy[0];

				if (ny < 0) {
					map[y][x] = map[i][j];

					if (y != i) {
						map[i][j] = 0;
					}
					break;
				}

				if (check_map[ny][nx] == 1) {
					map[y][x] = map[i][j];

					if (y != i) {
						map[i][j] = 0;
					}
					break;
				}

				if (map[ny][nx] != 0 && map[ny][nx] != map[i][j]) {
					map[y][x] = map[i][j];
					
					if (y != i) {
						map[i][j] = 0;
					}
					break;
				}

				if (map[ny][nx] == map[i][j] ) {
					map[ny][nx] = map[ny][nx] * 2;
					check_map[ny][nx] = 1;
					map[i][j] = 0;
					break;
				}

				x = nx;
				y = ny;
			}
		}
	}
}

void rmove() {

	int check_map[21][21] = {};

	for (int i = N-1; i >= 0; i--) {
		for (int j = N-1; j >= 0; j--) {
			if (map[i][j] == 0) continue;

			int x = j;
			int y = i;

			while (1) {
				int nx = x + dx[1];
				int ny = y + dy[1];

				if (nx >= N) {
					map[y][x] = map[i][j];

					if (x != j) {
						map[i][j] = 0;
					}
					break;
				}

				if (check_map[ny][nx] == 1) {
					map[y][x] = map[i][j];

					if (x != j) {
						map[i][j] = 0;
					}
					break;
				}

				if (map[ny][nx] != 0 && map[ny][nx] != map[i][j]) {
					map[y][x] = map[i][j];

					if (x != j) {
						map[i][j] = 0;
					}
					break;
				}

				if (map[ny][nx] == map[i][j] ) {
					map[ny][nx] = map[ny][nx] * 2;
					check_map[ny][nx] = 1;
					map[i][j] = 0;
					break;
				}

				x = nx;
				y = ny;
			}
		}
	}
}

void dmove() {

	int check_map[21][21] = {};

	for (int j = 0; j < N; j++) {
		for (int i = N-1; i >= 0; i--) {
			if (map[i][j] == 0) continue;

			int x = j;
			int y = i;

			while (1) {
				int nx = x + dx[2];
				int ny = y + dy[2];

				if (ny >= N) {
					map[y][x] = map[i][j];

					if (y != i) {
						map[i][j] = 0;
					}
					break;
				}

				if (check_map[ny][nx] == 1) {
					map[y][x] = map[i][j];

					if (y != i) {
						map[i][j] = 0;
					}
					break;
				}

				if (map[ny][nx] != 0 && map[ny][nx] != map[i][j]) {
					map[y][x] = map[i][j];

					if (y != i) {
						map[i][j] = 0;
					}
					break;
				}

				if (map[ny][nx] == map[i][j] ) {
					map[ny][nx] = map[ny][nx] * 2;
					check_map[ny][nx] = 1;
					map[i][j] = 0;
					break;
				}

				x = nx;
				y = ny;
			}
		}
	}

}

void lmove() {

	int check_map[21][21] = {};

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 0) continue;

			int x = j;
			int y = i;

			while (1) {
				int nx = x + dx[3];
				int ny = y + dy[3];

				if (nx< 0) {
					map[y][x] = map[i][j];

					if (x != j) {
						map[i][j] = 0;
					}
					break;
				}

				if (check_map[ny][nx] == 1) {
					map[y][x] = map[i][j];

					if (x != j) {
						map[i][j] = 0;
					}
					break;
				}

				if (map[ny][nx] != 0 && map[ny][nx] != map[i][j]) {
					map[y][x] = map[i][j];

					if (x != j) {
						map[i][j] = 0;
					}
					break;
				}

				if (map[ny][nx] == map[i][j] && check_map[ny][nx] != 1) {
					map[ny][nx] = map[ny][nx] * 2;
					check_map[ny][nx] = 1;
					map[i][j] = 0;
					break;
				}

				x = nx;
				y = ny;
			}
		}
	}
}

void move(int d) {

	if (d == 0) {
		umove();
	}
	else if (d == 1) {
		rmove();
	}
	else if (d == 2) {
		dmove();
	}
	else {
		lmove();
	}
}

void print() {
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void dfs(int level, int d) {

	//5회후 확인;
	if (level == 6) {
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				if (mmax < map[i][j]) {
					mmax = map[i][j];
				}
			}
		}
		return;
	}

	
	if (level != 0) {
		move(d);
	}

	//cout << level << "\n";
	//print();

	int cp_map[21][21] = {};

	for (int k = 0; k < 4; k++){

		//맵복사
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cp_map[i][j] = map[i][j];
			}
		}

		dfs(level + 1, k);
		//원복
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				map[i][j] = cp_map[i][j];
			}
		}
	}
}

void solve() {
	dfs(0, 0);
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