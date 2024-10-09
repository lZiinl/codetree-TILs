#define _CRT_SERCURE_NO_WARNINGS
#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

int R, C, W;
int map[35][35];

void input() {
	cin >> R >> C >> W;
}

void fmake() {
	for (int i = 1; i < 35; i++) {
		for (int j = 1; j <= i; j++) {
			if (j == 1 || i == j) {
				map[i][j] = 1;
			}
			else {
				map[i][j] = map[i - 1][j - 1] + map[i - 1][j];
			}
		}
	}
}

void paskal() {
	int result = 0;

	for (int i = 0; i < W; i++){
		for (int j = C; j <= C+i; j++){
			//cout << map[i][j] << " ";
			result += map[R+i][j];
		}
	}
	cout << result;
}

void solve() {

	fmake();
	paskal();

}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	solve();

	return 0;
}