#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int X, Y, D;
int map[51][51];
int vis[51][51];

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

struct Node{
	int y, x;
};

void input() {
	cin >> N >> M;
	cin >> Y >> X >> D;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			cin >> map[i][j];
		}
	}
}

void move() {

	map[Y][X] = 2;

	int nx = 0;
	int ny = 0;

	queue<Node> q;
	q.push({ Y,X });

	while (!q.empty()) {

		Node now = q.front();

		q.pop();
		int flag = 0;

		for (int i = 0; i < 4; i++) {

			D = (D + 3) % 4;

			nx = now.x + dx[D];
			ny = now.y + dy[D];

			if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
			if (map[ny][nx] != 0) continue;

			q.push({ ny,nx });
			map[ny][nx] = 2;
			flag = 1;
			break;
		}

		if (flag == 1) continue;

		nx = now.x - dx[D];
		ny = now.y - dy[D];

		if (map[ny][nx] == 1) return;

		q.push({ ny,nx });
	}

}

void cal() {
	int cnt = 0;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			if (map[i][j] == 2) cnt++;
		}
	}

	cout << cnt;
}

void solve() {

	move();
	cal();
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