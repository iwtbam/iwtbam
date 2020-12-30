#include <cstdio>
#include <time.h>
#include <cstring>
#include <cstdlib>

char line[3][30];
int vis[30];
int order[30];
int tot;
int value[300];

bool solve(int step, int n);
bool valid(int);
bool issolve(int);

int main()
{
    int n;
    scanf("%d", &n);
    scanf("%s%s%s", line[0], line[1], line[2]);

    for (int j = n - 1; j >= 0; j--)
    {
        for (int i = 0; i < 3; i++)
        {
            if (vis[line[i][j] - 'A'])
                continue;
            vis[line[i][j] - 'A'] = 1;
            order[tot] = line[i][j];
            tot++;
        }
    }

    memset(vis, 0, sizeof(vis));
    memset(value, -1, sizeof(value));
    solve(0, n);
    for (int i = 0; i < n; i++)
        printf("%d ", value[i + 'A']);
    printf("\n");
    return 0;
}

bool solve(int step, int n)
{

    if (step == n)
        return issolve(n);

    for (int i = n - 1; i >= 0; i--)
    {
        if (vis[i])
            continue;

        bool flag = true;
        value[order[step]] = i;
        vis[i] = 1;
        if (valid(n) && solve(step + 1, n))
            return true;
        value[order[step]] = -1;
        vis[i] = 0;
    }

    return false;
}

bool valid(int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        int a = value[line[0][i]];
        int b = value[line[1][i]];
        int c = value[line[2][i]];

        if (a == -1 || b == -1 || c == -1 || c == (a + b) % n || c == (a + b + 1) % n)
            continue;

        return false;
    }

    return true;
}

bool issolve(int n)
{
    int co = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int a = value[line[0][i]];
        int b = value[line[1][i]];
        int c = value[line[2][i]];

        if (a == -1 || b == -1 || c == -1)
            return false;
        if (c != (a + b + co) % n)
            return false;
        co = (a + b + co) / n;
    }

    return co == 0;
}