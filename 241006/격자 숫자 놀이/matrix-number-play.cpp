#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int map[101][101];
int number_cnt[101];

int R, C, K;
int result;

void input() {
	cin >> R >> C >> K;

	for (int i = 1; i <= 3; i++){
		for (int j = 1; j <= 3; j++){
			cin >> map[i][j];
		}
	}
}

void find() {
	int time = 0;
	int hang = 3;
	int yul = 3;

	while (1) {

		if (map[R][C] == K) {
			result = time;
			return;
		}

		if (time > 100) {
			result = -1;
			return;
		}

		vector<int>v;

		if (hang >= yul) {
			for (int i = 1; i <= hang; i++) {
				vector<pair<int, int>>tv;
				memset(number_cnt, 0, sizeof(number_cnt));

				for (int j = 1; j <= yul; j++) number_cnt[map[i][j]]++;
				for (int j = 1; j < 101; j++) {
					if (number_cnt[j] == 0) continue;
					tv.push_back(make_pair( number_cnt[j], j));
				}

				sort(tv.begin(), tv.end());

				for (int j = 1; j <= yul; j++) map[i][j] = 0;
				int index = 1;

				for (int j = 0; j < tv.size(); j++) {
					map[i][index++] = tv[j].second;
					map[i][index++] = tv[j].first;
				}
				index--;
				v.push_back(index);
			}
			sort(v.begin(), v.end());
			yul = v.back();
		}
		else {
			for (int i = 1; i <= yul; i++) {
				vector<pair<int, int>>tv;
				memset(number_cnt, 0, sizeof(number_cnt));

				for (int j = 1; j <= hang; j++) number_cnt[map[i][j]]++;
				for (int j = 1; j < 101; j++) {
					if (number_cnt[j] == 0) continue;
					tv.push_back(make_pair( number_cnt[j], j));
				}

				sort(tv.begin(), tv.end());

				for (int j = 1; j <= hang; j++) map[i][j] = 0;
				int index = 1;

				for (int j = 0; j < tv.size(); j++) {
					map[index++][i] = tv[j].second;
					map[index++][i] = tv[j].first;
				}
				index--;
				v.push_back(index);
			}
			sort(v.begin(), v.end());
			hang = v.back();
		}
		time++;
	}
}
	

void solve() {
	if (map[R][C] == K) {
		cout << result;
		return;
	}
	find();
	cout << result;
}

int main() {

	//freopen("sample.txt", "r", stdin);
	input();
	solve();

	return 0;
}