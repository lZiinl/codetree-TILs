#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int map[22][22];
int vis[22];

int mmin = 21e8;

void input() {
	cin >> N;

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			cin >> map[i][j];
		}
	}
}

void check() {

	vector<int>v1;
	vector<int>v2;

	for (int i = 1; i <= N; i++){
		if (vis[i] == 1) v1.push_back(i);
		else v2.push_back(i);
	}

	int sum1 = 0;
	int sum2 = 0;

	for (int i = 0; i < v1.size(); i++){
		for (int j = 0; j < v1.size(); j++){
			sum1 += map[v1[i]][v1[j]];
		}
	}

	for (int i = 0; i < v2.size(); i++) {
		for (int j = 0; j < v2.size(); j++) {
			sum2 += map[v2[i]][v2[j]];
		}
	}

	int result = abs(sum1 - sum2);

	if (result < mmin) mmin = result;
}

void dfs(int level, int s) {

	if (level == N / 2) {
		check();
		return;
	}

	for (int i = s; i <= N; i++){
		vis[i] = 1;
		dfs(level + 1, i + 1);
		vis[i] = 0;
	}
}

void solve() {

	for (int i = 1; i < N/2; i++){
		vis[i] = 1;
		dfs(1, i+1);
		vis[i] = 0;
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	//freopen("sample.txt", "r", stdin);

	input();
	solve();

	cout << mmin;

	return 0;
}