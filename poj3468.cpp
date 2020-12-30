#include <cmath>
#include <iostream>
#include <string>

using namespace std;

const int N = 100010;

int L[N], R[N], pos[N];
long long a[N], sum[N], add[N];

void build(int n);
void change(int l, int r, long long d);
long long ask(int l, int r);

int n, m, l, r;
long long d;
int len, num;

string s;

int main()
{
    std::ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(n);

    for (int i = 0; i < m; i++)
    {
        cin >> s >> l >> r;
        if (s[0] == 'C')
        {
            cin >> d;
            change(l - 1, r - 1, d);
        }
        else
        {
            cout << ask(l - 1, r - 1) << endl;
        }
    }
    return 0;
}

void build(int n)
{
    len = sqrt(n);
    num = n / len + (n % len != 0);

    for (int i = 0; i < num; i++)
    {
        L[i] = i * len;
        R[i] = (i + 1) * len - 1;
    }

    R[num - 1] = n - 1;

    for (int i = 0; i < n; i++)
        pos[i] = i / len;

    for (int i = 0; i < n; i++)
        sum[pos[i]] += a[i];
}

void change(int l, int r, long long d)
{
    int p = pos[l], q = pos[r];
    if (p == q)
    {
        for (int i = l; i <= r; i++)
            a[i] += d;

        sum[p] += (r - l + 1) * d;
    }
    else
    {
        for (int i = l; i <= R[p]; i++)
            a[i] += d;
        sum[p] += (R[p] - l + 1) * d;
        for (int i = L[q]; i <= r; i++)
            a[i] += d;
        sum[q] += (r - L[q] + 1) * d;
        for (int i = p + 1; i <= q - 1; i++)
            add[i] += d;
    }
}

long long ask(int l, int r)
{
    int p = pos[l], q = pos[r];
    long long total = 0;
    if (p == q)
    {
        for (int i = l; i <= r; i++)
            total += a[i];
        total += add[p] * (r - l + 1);
    }
    else
    {
        for (int i = l; i <= R[p]; i++)
            total += a[i];
        total += add[p] * (R[p] - l + 1);
        for (int i = L[q]; i <= r; i++)
            total += a[i];
        total += add[q] * (r - L[q] + 1);
        for (int i = p + 1; i <= q - 1; i++)
            total += sum[i] + add[i] * (R[i] - L[i] + 1);
    }
    return total;
}

#if 0

const int N = 100010;

struct SegmentNode
{
    int l;
    int r;
    long long sum;
    long long add;
};

SegmentNode nodes[N * 4];
long long val[N];
int n, m, l, r;
char str[2];
long long d;

void build(int no, int l, int r);
long long ask(int no, int l, int r);
void change(int no, int l, int r, long long v);
void spread(int no);

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &val[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s %d %d", str, &l, &r);
        if (str[0] == 'Q')
            printf("%lld\n", ask(1, l, r));
        else
        {
            scanf("%lld", &d);
            change(1, l, r, d);
        }
    }
    return 0;
}

void build(int no, int l, int r)
{
    nodes[no].l = l;
    nodes[no].r = r;

    if (nodes[no].l == nodes[no].r)
    {
        nodes[no].sum = val[l];
        nodes[no].add = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(no << 1, l, mid);
    build(no << 1 | 1, mid + 1, r);
    nodes[no].sum = nodes[no << 1].sum + nodes[no << 1 | 1].sum;
}

void change(int no, int l, int r, int long long v)
{
    if (l <= nodes[no].l && nodes[no].r <= r)
    {
        nodes[no].sum += v * (nodes[no].r - nodes[no].l + 1);
        nodes[no].add += v;
        return;
    }

    spread(no);

    int mid = (nodes[no].l + nodes[no].r) / 2;
    if (l <= mid)
        change(no << 1, l, r, v);

    if (r > mid)
        change(no << 1 | 1, l, r, v);

    nodes[no].sum = nodes[no << 1].sum + nodes[no << 1 | 1].sum;
}

long long ask(int no, int l, int r)
{
    if (l <= nodes[no].l && nodes[no].r <= r)
        return nodes[no].sum;
    spread(no);
    long long sum = 0;
    int mid = (nodes[no].l + nodes[no].r) / 2;
    if (l <= mid)
        sum += ask(no << 1, l, r);
    if (r > mid)
        sum += ask(no << 1 | 1, l, r);
    return sum;
}

void spread(int no)
{
    if (nodes[no].add == 0)
        return;
    int lc = no << 1, rc = no << 1 | 1;
    nodes[lc].sum += nodes[no].add * (nodes[lc].r - nodes[lc].l + 1);
    nodes[rc].sum += nodes[no].add * (nodes[rc].r - nodes[rc].l + 1);
    nodes[lc].add += nodes[no].add;
    nodes[rc].add += nodes[no].add;
    nodes[no].add = 0;
}

#endif
