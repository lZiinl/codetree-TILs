#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;
int map[12][12];
int plusmap[12][12];
vector<int> vmap[12][12];

int dx[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int dy[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };

void input(){
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			cin >> plusmap[i][j];
			map[i][j] = 5;
		}
	}

	for (int i = 0; i < M; i++){
		int t1, t2, t3;
		cin >> t1 >> t2 >> t3;
		vmap[t1][t2].push_back(t3);
	}
}

void eat() {

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){

			int vs = vmap[i][j].size();

			if (vs > 1) {
				sort(vmap[i][j].begin(), vmap[i][j].end());
			}

			for (int k = 0; k < vs; k++){
				if (map[i][j] >= vmap[i][j][k]) {
					map[i][j] -= vmap[i][j][k];
					vmap[i][j][k]++;
				}
				else {
					for (int l = vs-1; l >= k; l--){
						map[i][j] += vmap[i][j][l] / 2;
						vmap[i][j].pop_back();
					}
					break;
				}
			}
		}
	}
}

void dup() {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {

			int vs = vmap[i][j].size();

			for (int k = 0; k < vs; k++) {
				if (vmap[i][j][k] % 5 == 0) {

					for (int l = 0; l < 8; l++){

						int nx = j + dx[l];
						int ny = i + dy[l];

						if (nx < 1 || ny < 1 || nx > N || ny > N) continue;

						vmap[ny][nx].push_back(1);
					}
				}
			}
		}
	}
}

void add() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {

			map[i][j] = map[i][j] + plusmap[i][j];
		}
	}
}

void print() {

	int result = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			result += vmap[i][j].size();
		}
	}
	cout << result;
}

void solve() {

	for (int i = 0; i < K; i++){
		eat();
		dup();
		add();
	}
	print();
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	solve();

	return 0;
}