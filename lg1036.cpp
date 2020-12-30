#include <cstdio>
#include <algorithm>
#include <cmath>

using std::sort;

const int MAXN = 30;

long long nums[MAXN];
int vis[MAXN];
long long cans[MAXN];
int n, k;

int solve(int cur, int step);
int isprimer(long long num);

int main()
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%lld", &nums[i]);

    sort(nums, nums + n);
    printf("%d\n", solve(0, 0));
    return 0;
}

int solve(int c, int step)
{
    if (step > n || n - step < k - c)
        return 0;

    if (c == k)
    {
        long long sum = 0;
        for (int i = 0; i < c; i++)
            sum += cans[i];
        return isprimer(sum);
    }

    int ret = 0;

    for (int i = step; i < n; i++)
    {
        cans[c] = nums[i];
        ret += solve(c + 1, i + 1);
    }

    return ret;
}

int isprimer(long long num)
{
    int sq = sqrt(num);
    if (num <= 1)
        return 0;
    for (int i = 2; i <= sq; i++)
        if (num % i == 0)
            return 0;
    return 1;
}