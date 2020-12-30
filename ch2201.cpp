#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void solve(const vector<int> &cats, int cur, vector<int> &caps, int cnt, int W, int &ans)
{
    if (cnt >= ans)
        return;

    if (cur == cats.size())
    {
        ans = min(cnt, ans);
        return;
    }

    for (int i = 0; i < cnt; i++)
    {
        if (caps[i] + cats[cur] <= W)
        {
            caps[i] += cats[cur];
            solve(cats, cur + 1, caps, cnt, W, ans);
            caps[i] -= cats[cur];
        }
    }

    caps[cnt] += cats[cur];
    solve(cats, cur + 1, caps, cnt + 1, W, ans);
    caps[cnt] -= cats[cur];
    return;
}
int main()
{
    int N, W;
    cin >> N >> W;
    vector<int> cats(N + 1, 0);
    vector<int> caps(N + 1, 0);
    for (int i = 0; i < N; i++)
        cin >> cats[i];
    sort(cats.rbegin(), cats.rend());
    int ans = INT_MAX;
    solve(cats, 0, caps, 1, W, ans);
    cout << ans << endl;
    return 0;
}