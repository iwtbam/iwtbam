#include <iostream>
#include <queue>
#include <string>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::priority_queue;
using std::string;
using std::to_string;

struct State
{
    int city;
    int fuel;
    int cost;
    State(int ci, int f, int co) : city(ci), fuel(f), cost(co){};
};

namespace std
{
    template <>
    struct less<State>
    {
        bool operator()(const State &s1, const State &s2)
        {
            return s1.cost > s2.cost;
        }
    };

} // namespace std

const int MAX_NODE = 1010;
const int MAX_EDGE = 20010;
const int MAX_C = 101;
const int UN_SOLVE = 0x3f3f3f3f;

int head[MAX_NODE];
int cost[MAX_NODE];
int edge[MAX_EDGE];
int next[MAX_EDGE];
int weight[MAX_EDGE];

int dis[MAX_NODE][MAX_C];
bool vis[MAX_NODE][MAX_C];

int tot = 0;

void add(int x, int y, int z);
string solve(int s, int t, int c);

int main()
{
    int n, m, q;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> cost[i];
    for (int i = 0; i < m; i++)
    {
        int x, y, e;
        cin >> x >> y >> e;
        add(x, y, e);
        add(y, x, e);
    }
    cin >> q;
    int c, s, t;
    while (q--)
    {
        cin >> c >> s >> t;
        cout << solve(s, t, c) << endl;
    }
    return 0;
}

string solve(int s, int t, int c)
{
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<State> q;
    q.emplace(s, 0, 0);

    dis[s][0] = 0;

    while (q.size())
    {
        State s = q.top();
        int ci = s.city;
        int f = s.fuel;
        int co = s.cost;

        if (ci == t)
            return to_string(co);

        q.pop();
        if (f + 1 <= c && dis[ci][f] + cost[ci] < dis[ci][f + 1])
        {
            dis[ci][f + 1] = dis[ci][f] + cost[ci];
            q.emplace(ci, f + 1, dis[ci][f + 1]);
        }

        for (int i = head[ci]; i; i = next[i])
        {
            int nci = edge[i];
            int nw = weight[i];
            if (f < nw || co >= dis[nci][f - nw])
                continue;
            dis[nci][f - nw] = co;
            q.emplace(nci, f - nw, co);
        }
    }
    return "impossible";
}

void add(int x, int y, int z)
{
    edge[++tot] = y;
    weight[tot] = z;
    next[tot] = head[x];
    head[x] = tot;
}