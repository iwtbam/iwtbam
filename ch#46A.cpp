#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using namespace std;

const int N = 250010;

struct State
{
    long long dis, r;
    int p, m;
};

bool mcmp(const State &lhs, const State &rhs)
{
    return lhs.m < rhs.m;
}

bool dcmp(const State &lhs, const State &rhs)
{
    return lhs.dis < rhs.dis;
}

State states[N];

int pos[N], L[N], R[N], maxm[N];
int q[N], vis[N];

int main()
{
    int x0, y0, p0, r0, N, x, y, r;
    cin >> x0 >> y0 >> p0 >> r0 >> N;

    states[0].r = 1LL * r0 * r0;
    states[0].p = p0;

    for (int i = 1; i <= N; i++)
    {
        scanf("%d %d %d %d %d", &x, &y, &states[i].m, &states[i].p, &r);
        states[i].dis = 1LL * (x - x0) * (x - x0) + 1LL * (y - y0) * (y - y0);
        states[i].r = 1LL * r * r;
    }

    sort(states + 1, states + N + 1, mcmp);

    int len = sqrt(N);
    int t = N / len + (N % len != 0);

    for (int i = 1; i <= t; i++)
    {
        L[i] = len * (i - 1) + 1;
        R[i] = min(len * i, N);
        maxm[i] = states[R[i]].m;
        sort(states + L[i], states + R[i] + 1, dcmp);
    }

    int pL = 1, pR = 1;

    q[pL] = 0;

    while (pL <= pR)
    {
        int top = q[pL];

        int k = 0;

        for (int i = 1; i <= t; i++)
            if (maxm[i] <= states[top].p)
                k = i;
            else
                break;

        for (int i = 1; i <= k; i++)
        {
            while (L[i] <= R[i] && states[L[i]].dis <= states[top].r)
            {

                if (!vis[L[i]])
                {
                    q[++pR] = L[i];
                    vis[L[i]] = 1;
                }
                ++L[i];
            }
        }

        if (t != k++)
        {
            for (int l = L[k]; l <= R[k]; l++)
            {
                if (states[l].m > states[top].p || states[l].dis > states[top].r || vis[l])
                    continue;
                q[++pR] = l;
                vis[l] = 1;
            }
        }

        pL++;
    }

    cout << (pR - 1) << endl;
    return 0;
}