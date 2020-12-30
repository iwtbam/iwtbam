#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::lower_bound;
using std::max;
using std::sort;
using std::unique;

const int N = 2e4 + 10;

struct Line
{
    int x, y1, y2, c;
    bool operator<(const Line &rhs)
    {
        return x < rhs.x;
    }
};

struct SegmentNode
{
    int l;
    int r;
    long long data;
    long long add;
};

SegmentNode nodes[N * 4];
Line lines[N * 2];
int raws[N * 2];
void build(int no, int l, int r);
void change(int no, int l, int r, int c);
long long ask(int no, int l, int r);
void spread(int no);

int main()
{
    int m, w, h;
    while (cin >> m >> w >> h)
    {
        int x, y, c;
        for (int i = 1; i <= m; i++)
        {
            cin >> x >> y >> c;
            lines[i * 2 - 1] = {x, y, y + h - 1, c};
            lines[i * 2] = {x + w, y, y + h - 1, -c};
            raws[i * 2 - 1] = y;
            raws[i * 2] = y + h - 1;
        }

        sort(lines + 1, lines + m * 2 + 1);
        sort(raws + 1, raws + m * 2 + 1);
        int cnt = unique(raws + 1, raws + m * 2 + 1) - raws - 1;
        build(1, 1, cnt);
        long long ans = 0;
        for (int i = 1; i <= 2 * m; i++)
        {
            int p = lower_bound(raws + 1, raws + cnt + 1, lines[i].y1) - raws;
            int q = lower_bound(raws + 1, raws + cnt + 1, lines[i].y2) - raws - 1;
            change(1, p, q, lines[i].c);
            ans = max(ans, nodes[1].data);
        }

        cout << ans << endl;
    }
}

void build(int no, int l, int r)
{
    nodes[no] = {l, r, 0, 0};
    if (nodes[no].l == nodes[no].r)
        return;

    int mid = (nodes[no].l + nodes[no].r) / 2;
    build(no << 1, l, mid);
    build(no << 1 | 1, mid + 1, r);
}

void change(int no, int l, int r, int c)
{
    if (l <= nodes[no].l && nodes[no].r <= r)
    {
        nodes[no].add += c;
        nodes[no].data += c;
        return;
    }

    spread(no);

    int mid = (nodes[no].l + nodes[no].r) / 2;
    if (l <= mid)
        change(no << 1, l, mid, c);

    if (r > mid)
        change(no << 1 | 1, mid + 1, r, c);

    nodes[no].data = max(nodes[no << 1].data, nodes[no << 1 | 1].data);
}

void spread(int no)
{
    if (nodes[no].add == 0)
        return;
    nodes[no << 1].data += nodes[no].add;
    nodes[no << 1].add += nodes[no].add;
    nodes[no << 1 | 1].data += nodes[no].add;
    nodes[no << 1 | 1].add += nodes[no].add;
    nodes[no].add = 0;
}