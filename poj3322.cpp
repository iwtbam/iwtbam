#include <iostream>
#include <cstring>
#include <queue>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::string;
using std::to_string;

struct state
{
    int x;
    int y;
    int flag; // 0 : 立着, 1 : 横着, 2 : 竖着
    state(int x = 0, int y = 0, int flag = 0) : x(x), y(y), flag(flag){};
};

// 右 下 左 上
int next[3][4][3] = {
    {{0, 1, 1}, {1, 0, 2}, {0, -2, 1}, {-2, 0, 2}},
    {{0, 2, 0}, {1, 0, 1}, {0, -1, 0}, {-1, 0, 1}},
    {{0, 1, 2}, {2, 0, 0}, {0, -1, 2}, {-1, 0, 0}}};

const int MAXN = 501;
int M, N;
char grid[MAXN][MAXN];
int vis[MAXN][MAXN][3];

bool check(int x, int y, int flag);
string solve(int sx, int sy, int sl, int ex, int ey);

int main()
{

    while (cin >> M >> N && M && N)
    {
        int sx = -1, sy = -1, sl = 0, ex, ey;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] == 'X')
                {
                    if (sx == -1)
                    {
                        sx = i;
                        sy = j;
                    }
                    else
                    {
                        sl = i == sx ? 1 : 2;
                    }
                }
                else if (grid[i][j] == 'O')
                {
                    ex = i;
                    ey = j;
                }
            }
        }
        cout << solve(sx, sy, sl, ex, ey) << endl;
    }

    return 0;
}

bool check(int x, int y, int flag)
{
    if (grid[x][y] == '#')
        return false;
    if (flag == 0 && grid[x][y] == 'E')
        return false;
    if (flag == 1 && (y + 1 >= N || grid[x][y + 1] == '#'))
        return false;
    if (flag == 2 && (x + 1 >= M || grid[x + 1][y] == '#'))
        return false;
    return true;
}

string solve(int sx, int sy, int sl, int ex, int ey)
{
    queue<state> q;
    vis[sx][sy][sl] = 1;
    q.emplace(sx, sy, sl);
    int step = 0;
    while (q.size())
    {
        step++;
        size_t size = q.size();
        for (int i = 0; i < size; i++)
        {
            const state &f = q.front();
            for (int d = 0; d < 4; d++)
            {
                int nx = f.x + next[f.flag][d][0];
                int ny = f.y + next[f.flag][d][1];
                int nflag = next[f.flag][d][2];

                if (nx < 0 || nx >= M || ny < 0 || ny >= N || vis[nx][ny][nflag] || !check(nx, ny, nflag))
                    continue;

                if (nflag == 0 && grid[nx][ny] == 'O')
                    return to_string(step);
                vis[nx][ny][nflag] = 1;
                q.emplace(nx, ny, nflag);
            }
            q.pop();
        }
    }
    return "Impossible";
}