#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include <cstring>

using namespace std;

int N, M, P, C, D;
int ru_x, ru_y;

struct Santa
{
	int num, y, x, t, d;
};

vector<Santa> S;

int map[110][110];
bool isdie[31];
int score[31];

int dy[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };
int dx[8] = { 0, 1, 0, -1, -1, -1, 1, 1 };

int gametime;
int gameflag;

bool cmp(Santa a, Santa b) {

	if (a.d != b.d) return a.d < b.d;
	else {
		if (a.y != b.y) return a.y > b.y;
		else return a.x > b.x;
	}

}

bool cmp2(Santa a, Santa b) {
	return a.num < b.num;
}

void input() {

	cin >> N >> M >> P >> C >> D;
	cin >> ru_y >> ru_x;

	map[ru_y][ru_x] = -1;
	S.push_back({ 0,0,0,0 });
	for (int i = 1; i <= P; i++){
		int t1, t2, t3;
		cin >> t1 >> t2 >> t3;
		S.push_back({t1, t2, t3 });
		map[t2][t3] = t1;
	}

	sort(S.begin(), S.end(), cmp2);
}

void inter(int y, int x, int dir) {

	int n = map[y][x];

	map[y][x] = 0;
	S[n].x = S[n].x + dx[dir];
	S[n].y = S[n].y + dy[dir];

	if (S[n].x < 1 || S[n].y < 1 || S[n].x > N || S[n].y > N) {
		isdie[n] = true;
		return;
	}

	if (map[S[n].y][S[n].x] != 0) {
		inter(S[n].y, S[n].x, dir);
	}

	if (S[n].y > 0 && S[n].x > 0) {
		map[S[n].y][S[n].x] = n;
	}

}

void crash1(int n, int dir) {

	map[S[n].y][S[n].x] = 0;
	S[n].x = S[n].x + dx[dir] * C;
	S[n].y = S[n].y + dy[dir] * C;
	S[n].t = gametime + 2;

	if (S[n].x < 1 || S[n].y < 1 || S[n].x > N || S[n].y > N) {
		isdie[n] = true;
	}

	if (map[S[n].y][S[n].x] != 0) {
		inter( S[n].y, S[n].x, dir);
	}
	
	if (S[n].y > 0 && S[n].x > 0) {
		map[S[n].y][S[n].x] = n;
	}
}

void crash2(int n, int dir) {

	S[n].x = S[n].x + dx[dir] * D;
	S[n].y = S[n].y + dy[dir] * D;
	S[n].t = gametime + 2;

	if (S[n].x < 1 || S[n].y < 1 || S[n].x > N || S[n].y > N) {
		isdie[n] = true;
	}

	if (map[S[n].y][S[n].x] != 0) {
		inter(S[n].y, S[n].x, dir);
	}

	if (S[n].y > 0 && S[n].x > 0) {
		map[S[n].y][S[n].x] = n;
	}
}

void roodolf() {

	vector<Santa> tar;

	for (int i = 1; i <= P; i++){
		if (isdie[i] == true) continue;
		int dist = (S[i].x - ru_x) * (S[i].x - ru_x) + (S[i].y - ru_y) * (S[i].y - ru_y);
		tar.push_back({ S[i].num, S[i].y , S[i].x, 0, dist });
	}

	if (tar.size() == 0) {
		gameflag = 1;
		return;
	}

	sort(tar.begin(), tar.end(), cmp);
	int dir = 0;

	if (tar[0].x > ru_x && tar[0].y > ru_y) {
		dir = 6;
	}
	else if (tar[0].x > ru_x && tar[0].y < ru_y) {
		dir = 7;
	}
	else if (tar[0].x < ru_x && tar[0].y > ru_y) {
		dir = 5;
	}
	else if (tar[0].x < ru_x && tar[0].y < ru_y) {
		dir = 4;
	}
	else if (tar[0].x > ru_x && tar[0].y == ru_y) {
		dir = 1;
	}
	else if (tar[0].x < ru_x && tar[0].y == ru_y) {
		dir = 3;
	}
	else if (tar[0].x == ru_x && tar[0].y > ru_y) {
		dir = 2;
	}
	else if (tar[0].x == ru_x && tar[0].y < ru_y) {
		dir = 0;
	}

	map[ru_y][ru_x] = 0;
	ru_y += dy[dir];
	ru_x += dx[dir];

	if (tar[0].x == ru_x && tar[0].y == ru_y) {
		score[tar[0].num] += C;
		crash1(tar[0].num, dir);
	}
	map[ru_y][ru_x] = -1;
}

void moves() {

	for (int i = 1; i <= P; i++) {
		if (isdie[i] == true) continue;
		if (S[i].t > gametime) continue;

		int min_dist = (S[i].y - ru_y) * (S[i].y - ru_y) + (S[i].x - ru_x) * (S[i].x - ru_x);
		int dir = 10;

		for (int j = 0; j < 4; j++){
			int nx = S[i].x + dx[j];
			int ny = S[i].y + dy[j];

			if (map[ny][nx] > 0) continue;

			int dist = (ny - ru_y) * (ny - ru_y) + (nx - ru_x) * (nx - ru_x);

			if (dist < min_dist) {
				dir = j;
				min_dist = dist;
			}
		}

		if (dir != 10) {
			map[S[i].y][S[i].x] = 0;
			S[i].x += dx[dir];
			S[i].y += dy[dir];
		}

		if (S[i].x == ru_x && S[i].y == ru_y) {
			score[i] += D;
			crash2(i, (dir + 2) % 4);
		}

		if (S[i].y > 0 && S[i].x > 0) {
			map[S[i].y][S[i].x] = i;
		}
	}
}

void solve() {
	roodolf();
	if (gameflag == 1) return;
	moves();

	for (int i = 1; i <= P; i++){
		if (isdie[i] == true) continue;
		score[i]++;
	}
}

int main() {

	//freopen("sample.txt.", "r", stdin);

	input();

	for (int i = 1; i <= M; i++){
		gametime++;
		//cout << gametime << "\n";
		solve();
		if (gameflag == 1) break;
	}

	for (int i = 1; i <= P; i++){
		cout << score[i] << " ";
	}

	return 0;
}