#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 70

int R, C, K;
int forest[MAX + 3][MAX] = { 0, };

// 상우하좌(시계방향)
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0,1, 0, -1 };
bool exits[MAX + 3][MAX] = { false,0 };
int ans;

struct Golem
{
    int y, x;
    int d;
    int num;
};
queue<Golem> golems;

struct Point
{
    int y, x;
};

void input()
{
    cin >> R >> C >> K;
    for (int i = 1; i <= K; i++)
    {
        int x, dir;
        cin >> x >> dir;
        Golem a = { 0, x - 1, dir, i };
        golems.push(a);
    }
}

bool in_forest(int y, int x)
{
    bool flag;

    if (y >= 3 && y < R + 3 && x >= 0 && x < C) return true;
    else return false;
}

// y, x 에 위치할 수 있는지 체크
bool can_go(int y, int x)
{
    bool flag;
    if (x - 1 >= 0 && x + 1 < C && y + 1 < R + 3) flag = true;
    else flag = false;

    flag = flag && (forest[y - 1][x - 1] == 0);
    flag = flag && (forest[y - 1][x] == 0);
    flag = flag && (forest[y - 1][x + 1] == 0);

    flag = flag && (forest[y][x - 1] == 0);
    flag = flag && (forest[y][x] == 0);
    flag = flag && (forest[y][x + 1] == 0);

    flag = flag && (forest[y + 1][x] == 0);

    return flag;
}

// 숲 초기화
void reset_forest()
{
    for (int i = 0; i < R + 3; i++)
    {
        for (int j = 0; j < C; j++)
        {
            forest[i][j] = 0;
            exits[i][j] = false;
        }
    }
}

// 탐색
int bfs(Point st)
{
    int max_row = st.y;
    bool visited[MAX + 3][MAX] = { false, 0 };
    queue<Point> q;
    q.push(st);
    visited[st.y][st.x] = true;

    while (!q.empty())
    {
        Point now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            Point next = { now.y + dy[i], now.x + dx[i] };

            if (!in_forest(next.y, next.x)) continue; // 범위 체크
            if (visited[next.y][next.x]) continue; // 이미 방문한 곳 체크
            if (forest[next.y][next.x] == 0) continue; // 골렘이 없는 곳 체크
            if (!exits[now.y][now.x] && forest[next.y][next.x] != forest[now.y][now.x]) continue; // 현재 골렘의 출구가 아니면서 현재 골렘과 다음 골렘이 다른 경우 체크

            visited[next.y][next.x] = true;
            q.push(next);
            max_row = max(max_row, next.y);
        }
    }

    return max_row;
}

void down(Golem now)
{
    // 아래로 갈 수 있는 경우
    if (can_go(now.y + 1, now.x))
    {
        Golem next = { now.y + 1, now.x, now.d, now.num };
        down(next);
    }
    // 서쪽 아래로 갈 수 있는 경우
    else if (can_go(now.y + 1, now.x - 1))
    {
        Golem next = { now.y + 1, now.x - 1, (now.d + 3) % 4, now.num };
        down(next);
    }
    // 동쪽 아래로 갈 수 있는 경우
    else if (can_go(now.y + 1, now.x + 1))
    {
        Golem next = { now.y + 1, now.x + 1, (now.d + 1) % 4, now.num };
        down(next);
    }
    // 이동 불가
    else
    {
        // 숲을 벗어나는 경우
        if (!in_forest(now.y - 1, now.x - 1) || !in_forest(now.y + 1, now.x + 1))
        {
            reset_forest();
        }
        // 숲 안에 정착하는 경우
        else
        {
            // 숲에 골렘 기록
            forest[now.y][now.x] = now.num;
            for (int i = 0; i < 4; i++)
            {
                // 골렘 몸체 기록
                forest[now.y + dy[i]][now.x + dx[i]] = now.num;

                // 출구 기록
                exits[now.y + dy[now.d]][now.x + dx[now.d]] = true;
            }

            // 정령이 최대로 내려갈 수 있는 행 탐색 후 더하기
            ans += bfs({ now.y, now.x }) - 3 + 1;
        }
    }
}

void solution()
{
    // 모든 골렘들에 대해 진행
    while (!golems.empty())
    {
        Golem now = golems.front();
        golems.pop();

        // 내려가기
        down(now);
    }

    cout << ans << endl;
}

int main() {
    //freopen("sample.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}