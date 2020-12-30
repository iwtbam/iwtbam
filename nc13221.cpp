#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

const int L = 1001;

int f[L], s[L];

long long diff(int pf, int ps, int n)
{
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += 1L * (f[pf + i] - s[ps + i]) * (f[pf + i] - s[ps + i]);
    }

    return ans;
}

int main()
{
    int n, m;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", f + i);

    scanf("%d", &m);
    for (int j = 0; j < m; j++)
        scanf("%d", s + j);

    long long ans = INT_MAX;
    for (int i = 0; i < m - n + 1; i++)
    {
        ans = min(ans, diff(0, i, n));
    }

    printf("%d\n", ans);
}