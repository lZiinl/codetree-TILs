#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include<algorithm>

using namespace std;

int N, M, K;
bool isdie[402];
int gametime;

struct Node{
	int num, t; // 사람 번호랑 턴
};

struct Player{
	int num, y, x, d;
};

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

Node map[22][22];

//vector<int> debugmap[22][22];

vector<int> direction[402][4];
vector<Player>p;

bool cmp(Player a, Player b) {
	return a.num < b.num;
}

void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j].num << " ";
		}
		cout << "\n";
	}
}

void input() {
	cin >> N >> M >> K;

	p.push_back({ 0, 0, 0 }); //0번 인덱스에 사람 넣어두기

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			cin >> map[i][j].num;

			if (map[i][j].num != 0) {
				p.push_back({ map[i][j].num, i, j, 0 });
				map[i][j].t = K;
			}
		}
	}

	sort(p.begin(), p.end(), cmp);

	for (int i = 1; i <= M; i++){
		int t;
		cin >> t;
		p[i].d = (t + 3) % 4;
	}

	for (int i = 1; i <= M; i++){
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 4; k++){
				int temp;
				cin >> temp;
				temp = (temp + 3) % 4;
				direction[i][j].push_back(temp);
			}
		}
	}
}

void movep() {
	for (int i = 1; i <= M; i++){
		if (isdie[i] == true) continue;

		int n = p[i].num;
		int x = p[i].x;
		int y = p[i].y;
		int d = p[i].d;

		int nx;
		int ny;

		int flag = 0;

		for (int j = 0; j < 4; j++){

			ny = y + dy[direction[n][d][j]];
			nx = x + dx[direction[n][d][j]];

			if (nx < 1 || ny < 1 || nx > N || ny > N) continue;
			if (map[ny][nx].num == n && flag == 0) {
				flag = 1;
				p[n].x = nx;
				p[n].y = ny;
				p[n].d = direction[n][d][j];
			}

			if (map[ny][nx].num == 0) {
				p[n].x = nx;
				p[n].y = ny;
				p[n].d = direction[n][d][j];
				break;
			}
		}
	}
}

void buy() {
	for (int i = 1; i <= M; i++){
		if (isdie[i] == true) continue;

		int n = p[i].num;
		int x = p[i].x;
		int y = p[i].y;
		int d = p[i].d;

		if (map[y][x].num != n && map[y][x].num != 0) {
			isdie[n] = true;
			continue;
		}

		map[y][x].num = n;
		map[y][x].t = gametime + K;
	}
}

void erase() {
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			if (map[i][j].t > gametime) continue;

			map[i][j].num = 0;
			map[i][j].t = 0;
		}
	}
}

void solve() {
	//print();
	movep();
	buy();
	erase();
	//print();
}

int main() {

	//freopen("sample.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	input();
	//print();
	
	while (gametime < 999) {
		gametime++;
		solve();

		if (isdie[1] == true) {
			cout << -1;
			return 0;
		}

		int cnt = 0;

		for (int i = 1; i <= M; i++){
			if (isdie[i] == false) cnt++;

			if (cnt > 1) break;
			
		}

		if (cnt == 1) {
			cout << gametime;
			return 0;
		}
	}

	cout << -1;

	return 0;
}