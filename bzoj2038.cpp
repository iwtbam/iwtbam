#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 5e4 + 10;

int data[N], L[N], R[N], nums[N];
long long res[N][2];
int n, m;

long long ans = 0;

struct Query
{
    int l, r, id;
};

Query q[N];

inline long long gcd(long long a, long long b)
{
    return b ? gcd(b, a % b) : a;
}

bool lcmp(const Query &lhs, const Query &rhs)
{
    return lhs.l < rhs.l;
}

bool rcmp(const Query &lhs, const Query &rhs)
{
    return lhs.r < rhs.r;
}

void work(int x, int w)
{
    ans -= 1LL * nums[x] * (nums[x] - 1);
    nums[x] += w;
    ans += 1LL * nums[x] * (nums[x] - 1);
}

int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> data[i];
    for (int i = 1; i <= m; i++)
    {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    int len = sqrt(m);
    int t = m / len + (m % len != 0);

    sort(q + 1, q + m + 1, lcmp);

    for (int i = 1; i <= t; i++)
    {
        L[i] = len * (i - 1) + 1;
        R[i] = min(len * i, m);
        sort(q + L[i], q + R[i], rcmp);
    }

    for (int i = 1; i <= t; i++)
    {
        memset(nums, 0, sizeof(nums));

        ans = 0;
        int l = q[L[i]].l, r = q[L[i]].r;

        for (int j = l; j <= r; j++)
            work(data[j], 1);

        res[q[L[i]].id][0] = ans;
        res[q[L[i]].id][1] = 1LL * (r - l + 1) * (r - l);

        for (int j = L[i] + 1; j <= R[i]; j++)
        {
            while (r < q[j].r)
                work(data[++r], 1);

            while (r > q[j].r)
                work(data[r--], -1);

            while (l < q[j].l)
                work(data[l++], -1);

            while (l > q[j].l)
                work(data[--l], 1);

            res[q[j].id][0] = ans;
            res[q[j].id][1] = 1LL * (r - l + 1) * (r - l);
        }
    }

    for (int i = 1; i <= m; i++)
    {
        long long num = gcd(res[i][0], res[i][1]);
        if (num == 0)
        {
            res[i][0] = 0;
            res[i][1] = 1;
        }
        else
        {
            res[i][0] /= num;
            res[i][1] /= num;
        }

        cout << res[i][0] << "/" << res[i][1] << endl;
    }

    return 0;
}