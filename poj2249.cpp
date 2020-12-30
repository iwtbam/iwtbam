#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <deque>
#include <cstring>

using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::greater;
using std::pair;
using std::priority_queue;

using PII = pair<int, int>;

struct Edge
{
    int v, w, next;
    Edge(int v = 0, int w = 0, int n = 0) : v(v), w(w), next(n){};
};

const int MAX_N = 1001;
const int MAX_M = 100001;
const int INF = 0x3f3f3f3f;

int N, M;

int head[2][MAX_N];
Edge edges[2][MAX_M];
int tot[2] = {0};

int f[MAX_N];
int vis[MAX_N];
void add_edge(int no, int x, int y, int e);
void calc_f(int x);
int solve(int x, int y, int K);
int main()
{
    int x, y, e;
    int s, t, k;
    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        cin >> x >> y >> e;
        add_edge(0, x, y, e);
        add_edge(1, y, x, e);
    }
    cin >> s >> t >> k;
    cout << solve(s, t, k) << endl;
    return 0;
}

int solve(int x, int y, int K)
{
    calc_f(y);
    if (f[x] == INF)
        return -1;
    priority_queue<PII, deque<PII>, greater<PII>> q;
    q.emplace(f[x], x);
    while (q.size())
    {
        auto p = q.top();
        q.pop();
        int v = p.second, c = p.first;
        if (v == y)
        {
            K--;
            if (K == 0)
                return c - f[y];
        }
        for (int i = head[0][v]; i; i = edges[0][i].next)
        {
            int u = edges[0][i].v;
            int w = edges[0][i].w;
            q.emplace(c - f[v] + w + f[u], u);
        }
    }

    return -1;
}

void calc_f(int y)
{
    memset(vis, 0, sizeof(vis));
    memset(f, 0x3f, sizeof(f));

    priority_queue<PII, deque<PII>, greater<PII>> q;

    q.emplace(0, y);
    f[y] = 0;

    while (q.size())
    {
        auto p = q.top();
        q.pop();
        int v = p.second, c = p.first;
        vis[v] = 1;
        for (int i = head[1][v]; i; i = edges[1][i].next)
        {
            int u = edges[1][i].v, w = edges[1][i].w;
            //      cout << "v" << v << "u" << u << endl;

            if (!vis[u] && w + c < f[u])
            {
                f[u] = w + c;
                q.emplace(f[u], u);
            }
        }
    }
}

void add_edge(int no, int x, int y, int e)
{
    edges[no][++tot[no]].v = y;
    edges[no][tot[no]].w = e;
    edges[no][tot[no]].next = head[no][x];
    head[no][x] = tot[no];
}
