#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;

char grid[9][10];
int rows[9][10];
int cols[9][10];
int coords[9][10];
int pos[81][2];
int tot;

struct Zero
{
    int num, row;
} zeros[9];

bool cmp(const Zero &z1, const Zero &z2)
{
    return z1.num < z2.num;
}

bool solve(int step);

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        tot = 0;
        memset(rows, 0, sizeof(rows));
        memset(cols, 0, sizeof(cols));
        memset(zeros, 0, sizeof(zeros));
        memset(coords, 0, sizeof(coords));

        for (int i = 0; i < 9; i++)
        {
            zeros[i].row = i;
            scanf("%s", grid[i]);
            for (int j = 0; j < 9; j++)
            {
                char c = grid[i][j];
                if (c == '0')
                    zeros[i].num++;
                else
                {
                    int n = c - '0';
                    rows[i][n] = 1;
                    cols[j][n] = 1;
                    coords[(i / 3) * 3 + j / 3][n] = 1;
                }
            }
        }

        sort(zeros, zeros + 9, cmp);

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                int r = zeros[i].row;
                if (grid[r][j] == '0')
                {

                    pos[tot][0] = r;
                    pos[tot][1] = j;
                    tot++;
                }
            }
        };

        solve(0);
    }

    return 0;
}

bool solve(int step)
{
    if (step == tot)
    {
        for (int i = 0; i < 9; i++)
            printf("%s\n", grid[i]);
        return true;
    }

    int i = pos[step][0];
    int j = pos[step][1];

    for (int n = 1; n < 10; n++)
    {
        int cno = i / 3 * 3 + j / 3;
        if (rows[i][n] || cols[j][n] || coords[cno][n])
            continue;

        rows[i][n] = 1;
        cols[j][n] = 1;
        coords[cno][n] = 1;
        grid[i][j] = n + '0';
        if (solve(step + 1))
            return true;
        grid[i][j] = '0';
        rows[i][n] = 0;
        cols[j][n] = 0;
        coords[cno][n] = 0;
    }

    return false;
}
