#include <cstdio>

const int N = 9;

int grid[N][N];
int pos[81][2];
int rows[N][10];
int cols[N][10];
int coord[N][10];

int num = 0;

bool solve(int);

int main()
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] == 0)
            {
                pos[num][0] = i;
                pos[num][1] = j;
                num++;
            }
            else
            {
                int n = grid[i][j];
                rows[i][n] = 1;
                cols[j][n] = 1;
                int g = (i / 3) * 3 + j / 3;
                coord[g][n] = 1;
            }
        }
    }

    if (!solve(0))
        printf("-1\n");

    return 0;
}

bool solve(int step)
{
    if (step == num)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                printf("%d ", grid[i][j]);
            }
            printf("\n");
        }
        return true;
    }

    int i = pos[step][0];
    int j = pos[step][1];

    for (int n = 1; n <= 9; n++)
    {
        if (rows[i][n] || cols[j][n])
            continue;

        int g = (i / 3) * 3 + j / 3;

        if (coord[g][n])
            continue;

        grid[i][j] = n;
        rows[i][n] = 1;
        cols[j][n] = 1;
        coord[g][n] = 1;
        if (solve(step + 1))
            return true;
        rows[i][n] = 0;
        cols[j][n] = 0;
        coord[g][n] = 0;
        grid[i][j] = 0;
    }
    return false;
}