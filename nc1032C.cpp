#include <cstdio>
#include <cstring>

const int MAX_NUM = 100010;

long long A[MAX_NUM];
long long sum[MAX_NUM];
long long tree[2][MAX_NUM];

int n, m;

void add(int i, long long x, int type);
long long ask(int i, int type);

int main()
{
    char cmd[3];
    int l, r, d;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &A[i]);
        sum[i] = sum[i - 1] + A[i];
    }

    for (int i = 1; i <= m; i++)
    {
        scanf("%s", cmd);
        if (cmd[0] == 'Q')
        {
            scanf("%d %d", &l, &r);
            long long res = sum[r] - sum[l - 1];

            res += (r + 1) * ask(r, 0) - ask(r, 1);
            res -= l * ask(l - 1, 0) - ask(l - 1, 1);
            printf("%lld\n", res);
        }
        else
        {
            scanf("%d %d %d", &l, &r, &d);
            add(l, d, 0);
            add(r + 1, -d, 0);
            add(l, l * d, 1);
            add(r + 1, -(r + 1) * d, 1);
        }
    }
}

void add(int i, long long x, int type)
{
    while (i <= n)
    {
        tree[type][i] += x;
        i += i & (-i);
    }
}

long long ask(int i, int type)
{
    long long sum = 0;
    while (i > 0)
    {
        sum += tree[type][i];
        i -= i & (-i);
    }
    return sum;
}
