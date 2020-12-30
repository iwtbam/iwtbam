#include <cstdio>
#include <cstring>

const int MAX_NUM = 1e5 + 10;

long long tree[MAX_NUM];
int A[MAX_NUM];
int n, m;
void add(int i, int x);
long long ask(int i);

int main()
{
    memset(tree, 0, sizeof(tree));
    char cmd[3];
    scanf("%d %d", &n, &m);
    int l, r, d, x;
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < m; i++)
    {
        scanf("%s", cmd);
        if (cmd[0] == 'Q')
        {
            scanf("%d", &x);
            printf("%lld\n", A[x] * 1LL + ask(x));
        }
        else
        {
            scanf("%d %d %d", &l, &r, &d);
            add(l, d);
            add(r + 1, -d);
        }
    }

    return 0;
}

void add(int i, int x)
{
    while (i <= n)
    {
        tree[i] += x;
        i += i & (-i);
    }
}

long long ask(int i)
{
    long long sum = 0;
    while (i > 0)
    {
        sum += tree[i];
        i -= i & (-i);
    }
    return sum;
}