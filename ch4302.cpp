#include <cstdio>
#include <cstdlib>

const int N = 5e5;

struct SegmentNode
{
    int l;
    int r;
    long long ans;
};

SegmentNode nodes[N * 4];

long long a[N], b[N], tree[N];
int n, m, l, r;
long long d;
char str[2];

inline long long gcd(long long a, long long b);
void build(int no, int l, int r);
void change(int no, int x, long long v);
long long ask(int no, int l, int r);
void add(int i, int v);
long long sum(int i);

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        b[i] = a[i] - a[i - 1];
    }

    build(1, 1, n);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s %d %d", str, &l, &r);
        if (str[0] == 'C')
        {
            scanf("%lld", &d);
            add(l, d);
            add(r + 1, -d);
            change(1, l, d);
            if (r < n)
                change(1, r + 1, -d);
        }
        else
        {
            long long gcd_num = l < r ? ask(1, l + 1, r) : 0;
            long long sum_num = a[l] + sum(l);
            printf("%lld\n", gcd(sum_num, gcd_num));
        }
    }
}

inline long long gcd(long long a, long long b)
{
    return b ? gcd(b, a % b) : a;
}

void build(int no, int l, int r)
{
    nodes[no].l = l;
    nodes[no].r = r;
    if (nodes[no].l == nodes[no].r)
    {
        nodes[no].ans = b[l];
        return;
    }
    int mid = (l + r) / 2;
    build(no << 1, l, mid);
    build(no << 1 | 1, mid + 1, r);
    nodes[no].ans = gcd(nodes[no << 1].ans, nodes[no << 1 | 1].ans);
}

void change(int no, int x, long long v)
{
    if (nodes[no].l == nodes[no].r)
    {
        nodes[no].ans += v;
        return;
    }

    int mid = (nodes[no].l + nodes[no].r) / 2;
    if (x <= mid)
        change(no << 1, x, v);
    else
        change(no << 1 | 1, x, v);
    nodes[no].ans = gcd(nodes[no << 1].ans, nodes[no << 1 | 1].ans);
}

long long ask(int no, int l, int r)
{
    if (l <= nodes[no].l && nodes[no].r <= r)
        return abs(nodes[no].ans);

    int mid = (nodes[no].l + nodes[no].r) / 2;
    long long val = 0;
    if (l <= mid)
        val = gcd(ask(no << 1, l, r), val);
    if (r > mid)
        val = gcd(ask(no << 1 | 1, l, r), val);
    return val;
}

void add(int i, int v)
{
    while (i <= n)
    {
        tree[i] += v;
        i += i & (-i);
    }
}

long long sum(int i)
{
    long long total = 0;
    while (i > 0)
    {
        total += tree[i];
        i -= i & (-i);
    }
    return total;
}