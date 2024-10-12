#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int map[72][72];
int gol[3][3];

int R, C, K, D;

//골렘 중심 좌표
int sp_x, sp_y;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

// 게임 플레그 1 이면 시작불가
// 2 아래이동 불가
// 3 왼쪽아래 이동 불가
// 4 오른쪽아래 이동 불가 -> 전제 이동불가
int gameflag;

void input() {
	cin >> R >> C >> K;
}

void maperase() {
	map[sp_y][sp_x] = 0;
	for (int i = 0; i < 4; i++){
		int nx = sp_x + dx[i];
		int ny = sp_y + dy[i];

		map[ny][nx] = 0;
	}
}

void mapmake() {
	for (int i = sp_y - 1; i <= sp_y + 1; i++) {
		for (int j = sp_x - 1; j <= sp_x + 1; j++) {
			if (map[i][j] != 0) continue;
			map[i][j] = gol[i - sp_y + 1][j - sp_x + 1];
		}
	}
}

void print() {
	for (int i = 1; i <= R; i++){
		for (int j = 1; j <= C; j++){
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void makegol(int cnt) {
	gol[1][1] = cnt;
	for (int j = 0; j < 4; j++) {
		gol[1 + dy[j]][1 + dx[j]] = cnt;
	}
	gol[1 + dy[D]][1 + dx[D]] = -1;
}

void checkd() {
	if (sp_y + 1 >= R) {
		gameflag = 4;
	}

	if (map[sp_y + 1][sp_x - 1] != 0 || map[sp_y + 1][sp_x + 1] != 0 || map[sp_y + 2][sp_x] != 0) {
		gameflag = 2;
		return;
	}
}

void moved() {
	sp_y++;
}

void movel() {
	sp_y++;
	sp_x--;

	int temp = gol[0][1];
	gol[0][1] = gol[1][2];
	gol[1][2] = gol[2][1];
	gol[2][1] = gol[1][0];
	gol[1][0] = temp;
}

void mover() {
	sp_y++;
	sp_x++;

	int temp = gol[0][1];
	gol[0][1] = gol[1][0];
	gol[1][0] = gol[2][1];
	gol[2][1] = gol[1][2];
	gol[1][2] = temp;
 }

void checkl() {
	if (sp_x - 2 < 1) {
		gameflag = 3;
		return;
	}

	if (sp_y + 2 > R) {
		gameflag = 3;
	}

	if (map[sp_y - 1][sp_x - 1] != 0 || map[sp_y][sp_x - 2] != 0 ||
		map[sp_y + 1][sp_x - 1] != 0 || map[sp_y + 1][sp_x - 2] != 0 ||
		map[sp_y + 2][sp_x - 1] != 0) {
		gameflag = 3;
	}
}

void checkr() {
	if (sp_x + 2 > C) {
		gameflag = 4;
		return;
	}

	if (sp_y + 2 > R) {
		gameflag = 4;
	}

	if (map[sp_y - 1][sp_x + 1] != 0 || map[sp_y][sp_x + 2] != 0 ||
		map[sp_y + 1][sp_x + 1] != 0 || map[sp_y + 1][sp_x + 2] != 0 ||
		map[sp_y + 2][sp_x + 1] != 0) {
		gameflag = 4;
	}
}

void reset() {
	for (int i = 1; i <= R; i++){
		for (int j = 1; j <= C; j++){
			map[i][j] = 0;
		}
	}
}

int ans;
struct Node
{
	int y, x;
};

int vis[72][72];
vector<Node> v;

void bfs() {
	memset(vis, 0, sizeof(vis));

	queue<Node> q;
	q.push({ sp_y, sp_x });
	vis[sp_y][sp_x] = 1;
	int rmax = 0;

	while (!q.empty()) {

		Node now = q.front();
		q.pop();

		if (now.y > rmax) {
			rmax = now.y;
		}

		for (int i = 0; i < 4; i++){
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (vis[ny][nx] == 1) continue;
			if (map[ny][nx] == map[now.y][now.x] ) {
				q.push({ ny, nx });
				vis[ny][nx] = 1;
			}

			if (map[ny][nx] == -1) {
				int check = 0;

				for (int j = 0; j < v.size(); j++){
					if (v[j].y == now.y && v[j].x == now.x) {
						check = 1;
						break;
					}
				}

				if (check == 1) {
					q.push({ ny, nx });
					vis[ny][nx] = 1;
				}
			}

			if (map[now.y][now.x] == -1) {
				if (map[ny][nx] != 0) {
					q.push({ ny, nx });
					vis[ny][nx] = 1;
				}
			}
		}
	}

	ans += rmax;
}

void solve() {
	for (int i = 0; i < K; i++){
		cin >> sp_x >> D;
		sp_y = 0;
		gameflag = 0;

		int cnt = i + 1;

		makegol(cnt);
		mapmake();

		while (gameflag != 4) {
			gameflag = 0;

			//print();
			maperase();

			if (gameflag != 1) {
				
				checkd();
				if (gameflag == 0) {
					moved();
				}

				if (gameflag == 2) {
					checkl();
					if (gameflag == 2) {
						movel();
					}
				}

				if (gameflag == 3) {
					checkr();
					if (gameflag == 3) {
						mover();
					}
				}

				if (gameflag == 4) {
					if (sp_y < 2) {
						gameflag = 1;
					}
				}

			}

			if (gameflag == 1) {
				reset();
				v.clear();
				break;
			}

			mapmake();
		}

		v.push_back({ sp_y, sp_x });

		if (gameflag == 4) {
			bfs();
		}
	}
	cout << ans;
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