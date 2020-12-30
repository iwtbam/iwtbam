#include <iostream>
#include <algorithm>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::lower_bound;
using std::setprecision;
using std::sort;
using std::unique;

struct SegmentNode
{
    int l;
    int r;
    int cnt;
    double len;
};

struct Line
{
    double x, y1, y2;
    int k;
    bool operator<(const Line &other)
    {
        return x < other.x;
    }
};

const int N = 1e5 + 5;
Line lines[N * 4];
SegmentNode nodes[N * 4];
double raws[N * 4];

void merge(int no);
void build(int no, int l, int r);
void setLine(int no, double x, double y1, double y2, int k);
void change(int no, int l, int r, int k);

int n;

int main()
{
    int test_case_no = 1;
    std::ios::sync_with_stdio(false);
    double x1, x2;
    while (cin >> n && n != 0)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> x1 >> raws[i * 2 - 1] >> x2 >> raws[i * 2];
            setLine(i * 2 - 1, x1, raws[i * 2 - 1], raws[i * 2], 1);
            setLine(i * 2, x2, raws[i * 2 - 1], raws[i * 2], -1);
        }

        sort(raws + 1, raws + 2 * n + 1);
        sort(lines + 1, lines + 2 * n + 1);

        int cnt = unique(raws + 1, raws + 2 * n + 1) - raws - 1;
        build(1, 1, cnt);
        double ans = 0;
        for (int i = 1; i <= n * 2; i++)
        {
            int p = lower_bound(raws + 1, raws + cnt + 1, lines[i].y1) - raws;
            int q = lower_bound(raws + 1, raws + cnt + 1, lines[i].y2) - raws - 1;
            change(1, p, q, lines[i].k);
            ans += (lines[i + 1].x - lines[i].x) * nodes[1].len;
        }
        cout << "Test case #" << test_case_no << endl;
        cout << "Total explored area: " << fixed << setprecision(2) << ans << endl;
        test_case_no++;
    }
    return 0;
}

void merge(int no)
{
    if (nodes[no].cnt > 0)
        nodes[no].len = raws[nodes[no].r + 1] - raws[nodes[no].l];
    else if (nodes[no].l == nodes[no].r)
        nodes[no].len = 0;
    else
        nodes[no].len = nodes[no << 1].len + nodes[no << 1 | 1].len;
}

void build(int no, int l, int r)
{
    nodes[no].l = l;
    nodes[no].r = r;
    if (nodes[no].l == nodes[no].r)
    {
        nodes[no].cnt = 0;
        nodes[no].len = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(no << 1, l, mid);
    build(no << 1 | 1, mid + 1, r);
    merge(no);
}

void change(int no, int l, int r, int k)
{
    if (l <= nodes[no].l && nodes[no].r <= r)
    {
        nodes[no].cnt += k;
        merge(no);
        return;
    }
    int mid = (nodes[no].l + nodes[no].r) / 2;
    if (l <= mid)
        change(no << 1, l, r, k);
    if (r > mid)
        change(no << 1 | 1, l, r, k);
    merge(no);
}

void setLine(int no, double x, double y1, double y2, int k)
{
    lines[no].x = x;
    lines[no].y1 = y1;
    lines[no].y2 = y2;
    lines[no].k = k;
}