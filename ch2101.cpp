#include <iostream>
#include <bitset>

using std::bitset;
using std::cin;
using std::cout;
using std::endl;

const int MAXN = 30001;
const int MAXM = 30001;

bitset<MAXN> f[MAXN];
int next[MAXM];
int ver[MAXM];
int head[MAXN];

int node = 0;

int vis[MAXN];

void add_edge(int x, int y)
{
    ver[++node] = y;
    next[node] = head[x];
    head[x] = node;
}

void dfs(int x)
{
    vis[x] = 1;
    f[x].set(x, 1);
    // cout << x << endl;
    for (int n = head[x]; n != 0; n = next[n])
    {
        int y = ver[n];
        if (!vis[y])
            dfs(y);
        f[x] = f[x] | f[y];
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        add_edge(x, y);
    }

    for (int i = 1; i <= n; i++)
    {

        if (!vis[i])
            dfs(i);
    }

    for (int i = 1; i <= n; i++)
        cout << f[i].count() << endl;
    return 0;
}