#include <cstdio>
#include <cstring>

const int MAXN = 14;

int cols[MAXN];
int dia1[MAXN * 2];
int dia2[MAXN * 2];
int tot = 0;
int res[MAXN];

void solve(int, int);

int main()
{
    int N;
    while (scanf("%d", &N) != -1)
    {
        tot = 0;
        memset(dia1, 0, sizeof(dia1));
        memset(dia2, 0, sizeof(dia2));
        memset(cols, 0, sizeof(cols));
        solve(1, N);
        printf("%d\n", tot);
    }
    return 0;
}

void solve(int row, int N)
{
    if (row == N + 1)
    {
        if (tot < 3)
        {
            for (int i = 1; i <= N; i++)
                if (i != N)
                    printf("%d ", res[i]);
                else
                    printf("%d\n", res[i]);
        }
        tot++;
        return;
    }
    for (int c = 1; c <= N; c++)
    {
        if (cols[c] || dia1[row + c] || dia2[row - c + N])
            continue;
        cols[c] = 1;
        dia1[row + c] = 1;
        dia2[row - c + N] = 1;
        res[row] = c;
        solve(row + 1, N);
        cols[c] = 0;
        dia1[row + c] = 0;
        dia2[row - c + N] = 0;
    }
}
