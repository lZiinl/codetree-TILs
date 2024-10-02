#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int N, M;
int map[8][8];
struct Point {
    int x, y;
};

vector<Point> cam;
int ans = 21e8;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void input() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] > 0 && map[i][j] < 6)
                cam.push_back({ i, j });
        }
    }
}

void check(int y, int x, int dir) {
    dir = dir % 4;
    while (1) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        x = nx;
        y = ny;

        if (nx < 0 || ny < 0 || nx >= M || ny >= N) return;
        if (map[ny][nx] == 6) return;
        if (map[ny][nx] != 0) continue;

        map[ny][nx] = 7;
    }
}

void dfs(int level) {
    if (level == cam.size()) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j]==0) cnt++;
            }
        }
        if (ans > cnt) {
            ans = cnt;
        }
        return;
    }

    int x = cam[level].x;
    int y = cam[level].y;
    int tmp[9][9];

    for (int dir = 0; dir < 4; dir++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                tmp[i][j] = map[i][j];
            }
        } 

        if (map[x][y] == 1) check(x, y, dir);

        else if (map[x][y] == 2) {
            check(x, y, dir);
            check(x, y, dir + 2);
        }
        else if (map[x][y] == 3) {
            check(x, y, dir);
            check(x, y, dir + 1);
        }
        else if (map[x][y] == 4) {
            check(x, y, dir);
            check(x, y, dir + 1);
            check(x, y, dir + 2);
        }
        else if (map[x][y] == 5) {
            check(x, y, dir);
            check(x, y, dir + 1);
            check(x, y, dir + 2);
            check(x, y, dir + 3);
        }

        dfs(level + 1);
        // case 종료이므로 초기화
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                map[i][j] = tmp[i][j];
            }
        }   
    }
}

int main() {

    //freopen("sample.txt", "r", stdin);

    cin >> N >> M;
    input();
    dfs(0);
    cout << ans;

    return 0;
}