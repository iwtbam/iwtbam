#include <cstdio>
#include <queue>
#include <cstring>

using std::queue;

const int MAXN = 300;
const int INF = 0x3f3f3f3f;
int nums[MAXN];
int dis[MAXN];
int N;

int dirs[2] = {-1, 1};

int solve(int cur, int target);

int main()
{
    int A, B;
    scanf("%d%d%d", &N, &A, &B);

    for (int i = 0; i < N; i++)
        scanf("%d", &nums[i + 1]);

    printf("start!\n");
    printf("%d\n", solve(A, B));
    return 0;
}

int solve(int cur, int target)
{
    memset(dis, 0x3f, sizeof(dis));
    queue<int> q;
    q.emplace(cur);
    dis[cur] = 0;
    while (q.size())
    {
        int c = q.front();
        q.pop();
        for (int d = 0; d < 2; d++)
        {
            int n = c + dirs[d] * nums[c];
            printf("%d %d %d\n", c, n, dis[c]);
            if (n <= 0 || n > N || dis[c] + 1 >= dis[n])
                continue;
            dis[n] = dis[c] + 1;
            q.emplace(n);
        }
    }

    return dis[target] == INF ? -1 : dis[target];
}