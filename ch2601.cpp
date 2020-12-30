#include <iostream>
#include <deque>
#include <utility>
#include <cstring>
#include <string>

using namespace std;

int dxs[4] = {1, -1, -1, 1};
int dys[4] = {1, -1, 1, -1};

const int MAX_NUM = 501;

char grid[MAX_NUM][MAX_NUM];
int cost[MAX_NUM][MAX_NUM];
string solve(int, int);

const int NO_SULTION = 0x3f3f3f3f;

int main()
{
    int T, R, C;
    cin >> T;
    while (T && cin >> R >> C)
    {
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                cin >> grid[i][j];
            }
        }

        cout << solve(R, C) << endl;
        T--;
    }
}

string solve(int R, int C)
{
    deque<pair<int, int>> q;
    q.emplace_back(0, 0);

    memset(cost, 0x3f, sizeof(cost));

    cost[0][0] = 0;

    while (q.size())
    {
        auto front = q.front();
        int cx = front.first;
        int cy = front.second;
        q.pop_front();

        for (int d = 0; d < 4; d++)
        {
            int nx = cx + dxs[d];
            int ny = cy + dys[d];
            if (nx < 0 || nx > R || ny < 0 || ny > C)
                continue;
            int x = min(cx, nx);
            int y = min(cy, ny);

            if ((grid[x][y] == '\\' && (d == 0 || d == 1)) || (grid[x][y] == '/' && (d == 2 || d == 3)))
            {
                if (cost[cx][cy] < cost[nx][ny])
                {
                    cost[nx][ny] = cost[cx][cy];
                    q.emplace_front(nx, ny);
                }
            }
            else
            {
                if (cost[cx][cy] + 1 < cost[nx][ny])
                {
                    cost[nx][ny] = cost[cx][cy] + 1;
                    q.emplace_back(nx, ny);
                }
            }
        }
    }

    return cost[R][C] == NO_SULTION ? "NO SOLUTION" : to_string(cost[R][C]);
}