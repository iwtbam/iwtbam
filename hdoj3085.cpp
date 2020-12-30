#include <iostream>
#include <queue>
#include <utility>

using namespace std;

const int MAX_NUM = 801;

char grid[MAX_NUM][MAX_NUM];

int dxs[4] = {0, 0, 1, -1};
int dys[4] = {1, -1, 0, 0};
int mx, my, gx, gy;

int ghx[2] = {-1};
int ghy[2] = {-1};

int M, N;

bool expand(queue<pair<int, int>> &q, char s, char t, int k);
int solve();

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> M >> N;
        ghx[0] = -1;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> grid[i][j];

                if (grid[i][j] == 'M')
                {
                    mx = i;
                    my = j;
                }

                if (grid[i][j] == 'G')
                {
                    gx = i;
                    gy = j;
                }

                if (grid[i][j] == 'Z')
                {
                    if (ghx[0] == -1)
                    {
                        ghx[0] = i;
                        ghy[0] = j;
                    }
                    else
                    {
                        ghx[1] = i;
                        ghy[1] = j;
                    }
                }
            }
        }

        cout << solve() << endl;
    }

    return 0;
}

bool safe(int x, int y, int k)
{
    bool ret = true;
    for (int i = 0; i < 2; i++)
    {
        ret = ret && (abs(ghx[i] - x) + abs(ghy[i] - y) > 2 * k);
    }
    return ret;
}

int solve()
{
    queue<pair<int, int>> mq;
    queue<pair<int, int>> gq;
    mq.emplace(mx, my);
    gq.emplace(gx, gy);
    int k = 1;
    while (mq.size() || gq.size())
    {
        for (int i = 0; i < 3; i++)
        {
            if (mq.size() && expand(mq, 'M', 'G', k))
                return k;
        }

        if (gq.size() && expand(gq, 'G', 'M', k))
            return k;

        k++;
    }

    return -1;
}

bool expand(queue<pair<int, int>> &q, char s, char t, int k)
{
    size_t size = q.size();
    for (int j = 0; j < size; j++)
    {
        auto f = q.front();
        q.pop();
        int cx = f.first;
        int cy = f.second;
        if (!safe(cx, cy, k))
            continue;
        for (int d = 0; d < 4; d++)
        {
            int nx = cx + dxs[d];
            int ny = cy + dys[d];
            if (nx < 0 || nx >= M || ny < 0 || ny >= N || grid[nx][ny] == 'X' || grid[nx][ny] == s || !safe(nx, ny, k))
                continue;

            if (grid[nx][ny] == t)
                return true;

            grid[nx][ny] = s;
            q.emplace(nx, ny);
        }
    }
    return false;
}