#include <cstdio>
#include <cstring>
#include <algorithm>
#include <time.h>

using std::sort;

char line[82];

int rows[9];
int cols[9];
int coords[9];
int cnt[1 << 9];
int nums[1 << 9];

int pos[81][2];
int vis[81];
int tot;

void filp(int r, int c, int n)
{
    rows[r] ^= 1 << n;
    cols[c] ^= 1 << n;
    coords[r / 3 * 3 + c / 3] ^= 1 << n;
}

bool solve(int step);

int main()
{
    time_t now = clock();

    for (int i = 1; i < (1 << 9); i++)
        for (int j = i; j; j -= j & (-j))
            cnt[i]++;

    for (int i = 0; i < 9; i++)
        nums[1 << i] = i;

    while (scanf("%s", line) != -1 && strcmp(line, "end") != 0)
    {
        tot = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < 9; i++)
        {
            rows[i] = (1 << 9) - 1;
            cols[i] = (1 << 9) - 1;
            coords[i] = (1 << 9) - 1;
        }

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                char c = line[i * 9 + j];
                if (c != '.')
                    filp(i, j, c - '1');
                else
                {
                    pos[tot][0] = i;
                    pos[tot][1] = j;
                    tot++;
                }
            }
        }
        solve(0);
    }

    //  printf("time cost : %lf s\n", (clock() - now) * 1.0 / CLOCKS_PER_SEC);
    return 0;
}

bool solve(int step)
{
    if (step == tot)
    {
        printf("%s\n", line);
        return true;
    }

    int num = 10, p;
    for (int k = 0; k < tot; k++)
    {
        if (vis[k])
            continue;
        int i = pos[k][0];
        int j = pos[k][1];
        int s = rows[i] & cols[j] & coords[i / 3 * 3 + j / 3];
        if (cnt[s] < num)
        {
            num = cnt[s];
            p = k;
        }
    }

    int i = pos[p][0];
    int j = pos[p][1];
    int s = rows[i] & cols[j] & coords[i / 3 * 3 + j / 3];

    vis[p] = 1;
    while (s)
    {
        int n = nums[s & (-s)];
        filp(i, j, n);
        line[i * 9 + j] = n + '1';
        if (solve(step + 1))
            return true;
        line[i * 9 + j] = '.';
        filp(i, j, n);
        s -= s & (-s);
    }
    vis[p] = 0;

    return false;
}
