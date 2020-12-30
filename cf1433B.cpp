#include <cstdio>
#include <algorithm>
#include <cstring>

using std::min;

const int MAX_NUM = 300;
const int INF = 0x3f3f3f3f;

int dp[3][MAX_NUM][MAX_NUM];
int nums[MAX_NUM];
int ones[MAX_NUM];

int main()
{
    int t, n;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &nums[i]);
            ones[i] = ones[i - 1] + nums[i];
        }

        memset(dp, 0x3f, sizeof(dp));

        for (int i = 1; i <= n; i++)
        {
            dp[0][i][i] = 0;
            dp[1][i][i] = 0;
            dp[2][i][i] = 0;
        }

        for (int len = 2; len <= n; len++)
        {
            for (int i = 1; i <= n - len + 1; i++)
            {
                int j = i + len - 1;

                for (int k = i; k < j; k++)
                {
                    int L = k - i + 1;
                    int R = len - L;
                    if (ones[j] - ones[k] != 0)
                        dp[0][i][j] = min(dp[0][i][j], dp[0][i][k] + dp[0][k + 1][j] + L - (ones[k] - ones[i - 1]));
                    else
                        dp[0][i][j] = min(dp[0][i][j], dp[0][i][k] + dp[0][k + 1][j]);

                    if (ones[k] - ones[i - 1] != 0)
                        dp[1][i][j] = min(dp[1][i][j], dp[1][i][k] + dp[1][k + 1][j] + R - (ones[j] - ones[k]));
                    else
                        dp[1][i][j] = min(dp[1][i][j], dp[1][i][k] + dp[1][k + 1][j]);

                    dp[2][i][j] = min(dp[2][i][j], dp[1][i][k] + dp[0][k + 1][j]);
                }
            }
        }

        int res = min(dp[0][1][n], min(dp[1][1][n], dp[2][1][n]));
        printf("%d\n", res);
    }
    return 0;
}