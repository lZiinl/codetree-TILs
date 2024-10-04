#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;

int N;
int sp_x, sp_y, d, g;
int map[101][101];

// 0 우
// 1 상
// 2 좌
// 3 하
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };

void input() {
	cin >> sp_y >> sp_x >> d >> g;
}

void solve() {
	int x = sp_x;
	int y = sp_y;
	int dir = d;
	vector<int> v;
	vector<int> temp1;
	vector<int> temp2;
	v.push_back(dir);

	map[y][x] = 1;

	for (int i = 0; i <= g; i++){

		for (int j = 0; j < v.size(); j++){
			y = y + dy[v[j]];
			x = x + dx[v[j]];

			map[y][x] = 1;
		}

		temp1.clear();
		temp2.clear();
		int vsize = v.size();

		for (int j = 0; j < vsize; j++){
			temp1.push_back((v[j]));
		}

		for (int j = 0; j < vsize; j++) {
			temp2.push_back((v.back() + 1) % 4);
			v.pop_back();
		}

		v.insert(v.begin(), temp1.begin(), temp1.end());
		v.insert(v.begin(), temp2.begin(), temp2.end());

		if (i == 0) {
			v.pop_back();
		}
	}
}

void count() {
	int cnt = 0;

	for (int i = 0; i < 101; i++){
		for (int j = 0; j < 101; j++){
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1) {
				cnt++;
			}
		}
	}

	cout << cnt;
}


int main() {
	//freopen("sample.txt", "r", stdin);

	cin >> N;

	for (int i = 0; i < N; i++) {
		input();
		solve();
	}

	count();

	return 0;
}