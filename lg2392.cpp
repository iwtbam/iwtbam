#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <cstring>

using std::max;
using std::min;

const int MAXN = 100;
const int INF = 0x3f3f3f3f;

int num[MAXN];
int dp[3000];

int partition(int *, int);
int calc(int *, int);
int main()
{
    int s1, s2, s3, s4;
    scanf("%d%d%d%d", &s1, &s2, &s3, &s4);
    int cost = 0;
    cost += calc(num, s1);
    cost += calc(num, s2);
    cost += calc(num, s3);
    cost += calc(num, s4);
    printf("%d\n", cost);

    return 0;
}

int calc(int *num, int size)
{
    for (int i = 0; i < size; i++)
        scanf("%d", &num[i]);
    return partition(num, size);
}

int partition(int *num, int total)
{
    int sum = 0;
    for (int i = 0; i < total; i++)
        sum += num[i];

    int half = sum / 2;
    memset(dp, 0, sizeof(dp));

    dp[0] = 1;
    for (int i = 0; i < total; i++)
    {
        for (int j = half; j >= num[i]; j--)
        {
            if (dp[j] == 0)
                dp[j] = dp[j - num[i]];
        }
    }

    int res = INF;
    for (int i = 0; i <= half; i++)
    {
        if (dp[i] == 0)
            continue;
        res = min(res, max(i, sum - i));
    }

    return res;
}
