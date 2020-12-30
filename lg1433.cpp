#include <cstdio>
#include <cmath>
#include <algorithm>

using std::min;

const int MAXN = 20;
const double INF = 100000000;
double xs[MAXN];
double ys[MAXN];

int tot = 1;

double dis[MAXN][MAXN];
double f[1 << MAXN][MAXN];
int n;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &xs[i], &ys[i]);

    for (int i = 0; i < n + 1; i++)
    {
        for (int j = i; j < n + 1; j++)
        {
            dis[i][j] = sqrt(pow(xs[i] - xs[j], 2) + pow(ys[i] - ys[j], 2));
            dis[j][i] = dis[i][j];
        }
    }

    for (int state = 0; state < 1 << n + 1; state++)
    {
        for (int i = 0; i < n + 1; i++)
            f[state][i] = INF;
    }

    f[1][0] = 0;

    for (int state = 1; state < (1 << n + 1); state++)
    {
        for (int t = 1; t < n + 1; t++)
        {
            if (!(state >> t & 1))
                continue;
            for (int k = 0; k < n + 1; k++)
            {
                if (!((state ^ 1 << t) >> k & 1))
                    continue;
                f[state][t] = min(f[state][t], f[(state ^ 1 << t)][k] + dis[k][t]);
            }
        }
    }

    double ret = INF;
    for (int i = 1; i < n + 1; i++)
        ret = min(ret, f[(1 << n + 1) - 1][i]);
    printf("%-0.2lf\n", ret);
    return 0;
}

// queue<pair<int, int>> q;
// q.emplace(0, 1);
// dis[1] = 0;

// while (q.size())
// {
//     auto p = q.front();
//     q.pop();
//     int from = p.first;
//     int state = p.second;

//     for (int i = 1; i <= n; i++)
//     {
//         if (state & (1 << i) || from == i)
//             continue;

//         int nstate = state | (1 << i);
//         double diff = sqrt(pow(xs[from] - xs[i], 2) + pow(ys[from] - ys[i], 2));

//         if (dis[nstate] > 0 && dis[state] + diff >= dis[nstate])
//             continue;
//         dis[nstate] = dis[state] + diff;
//         q.emplace(i, nstate);
//     }
// }
