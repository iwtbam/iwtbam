#include <cstdio>
#include <algorithm>
#include <cstring>

using std::max;

const int N = 500001;

struct SegmentTree
{
    int l, r;
    int sum;
    int lmax;
    int rmax;
    int data;
};

SegmentTree segs[N * 4];
int datas[N];
int n, m;

void build(int root, int l, int r);
SegmentTree ask(int root, int l, int r);
void change(int root, int l, int r);
void merge(int k);

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &datas[i]);
    memset(segs, 0, sizeof(segs));
    build(0, 0, n - 1);
    SegmentTree res;
    int c, x, y;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &c, &x, &y);
        if (c == 1)
        {
            if (x <= y)
                res = ask(0, x - 1, y - 1);
            else
                res = ask(0, y - 1, x - 1);
            printf("%d\n", res.data);
        }
        else
            change(0, x - 1, y);
    }
    return 0;
}

void build(int root, int l, int r)
{
    segs[root].l = l;
    segs[root].r = r;

    if (l == r)
    {
        segs[root].lmax = datas[l];
        segs[root].rmax = datas[l];
        segs[root].sum = datas[l];
        segs[root].data = datas[l];
        return;
    }

    int mid = (l + r) / 2;
    int lc = root * 2 + 1, rc = root * 2 + 2;

    build(lc, l, mid);
    build(rc, mid + 1, r);
    merge(root);
}

SegmentTree ask(int root, int l, int r)
{
    if (l <= segs[root].l && segs[root].r <= r)
        return segs[root];
    int mid = (segs[root].l + segs[root].r) / 2;

    if (r <= mid)
        return ask(root * 2 + 1, l, mid);
    else if (l > mid)
        return ask(root * 2 + 2, mid + 1, r);

    SegmentTree lc = ask(root * 2 + 1, l, mid);
    SegmentTree rc = ask(root * 2 + 2, mid + 1, r);
    SegmentTree res;
    res.l = l;
    res.r = r;
    res.lmax = max(lc.lmax, lc.sum + rc.lmax);
    res.rmax = max(rc.rmax, rc.rmax + rc.sum);
    res.sum = lc.sum + rc.sum;
    res.data = max(max(lc.data, rc.data), lc.lmax + rc.rmax);

    return res;
}

void change(int root, int x, int v)
{
    if (segs[root].l == segs[root].r)
    {
        segs[root].lmax = v;
        segs[root].rmax = v;
        segs[root].data = v;
        segs[root].sum = v;
        return;
    }

    int mid = (segs[root].l + segs[root].r) / 2;
    int lc = root * 2 + 1, rc = root * 2 + 2;
    if (x <= mid)
        change(lc, x, v);
    else
        change(rc, x, v);

    merge(root);
}

void merge(int k)
{
    segs[k].lmax = max(segs[k * 2 + 1].lmax, segs[k * 2 + 1].sum + segs[k * 2 + 2].lmax);
    segs[k].rmax = max(segs[k * 2 + 2].rmax, segs[k * 2 + 1].rmax + segs[k * 2 + 2].sum);
    segs[k].sum = segs[k * 2 + 1].sum + segs[k * 2 + 2].sum;
    segs[k].data = max(max(segs[k * 2 + 1].data, segs[k * 2 + 2].data), segs[k * 2 + 1].rmax + segs[k * 2 + 2].lmax);
}
