#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100;

long long data[MAXN];

long long W, N;

long long search(const vector<long long> &ws, long long w)
{
    int l = 0, r = ws.size() - 1;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (ws[mid] + w <= W)
            l = mid;
        else
            r = mid - 1;
    }

    return ws[l] + w;
    s
}

void dfs1(int cur, int half, long long cw, vector<long long> &ws)
{
    if (cur == half)
    {
        ws.push_back(cw);
        return;
    }
    if (cw + data[cur] <= W)
        dfs1(cur + 1, half, cw + data[cur], ws);
    dfs1(cur + 1, half, cw, ws);
}

void dfs2(int cur, int end, long long cw, vector<long long> &ws, long long &ans)
{
    if (cur == end)
    {
        ans = max(ans, search(ws, cw));
        return;
    }
    if (cw + data[cur] <= W)
        dfs2(cur + 1, end, cw + data[cur], ws, ans);
    dfs2(cur + 1, end, cw, ws, ans);
}

int main()
{
    cin >> W >> N;

    for (int i = 0; i < N; i++)
        cin >> data[i];

    sort(data, data + N);
    reverse(data, data + N);

    int half = min(N / 2 + 1, N);

    vector<long long> ws;
    dfs1(0, half, 0, ws);

    sort(ws.begin(), ws.end());
    vector<long long>::iterator nend = unique(ws.begin(), ws.end());
    ws.erase(nend, ws.end());
    long long ans = *max_element(ws.begin(), ws.end());

    dfs2(half, N, 0, ws, ans);
    cout << ans << endl;
    return 0;
}