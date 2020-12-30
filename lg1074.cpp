#include <cstdio>
#include <algorithm>
#include <ctime>
#include <vector>

using std::max;
using std::stable_sort;
using std::vector;

const int N = 9;
const int INF = 0x3f3f3f3f;

int grid[N][N];
// int pos[81][2];
vector<vector<int>> pos(81, vector<int>(2));
int rows[N][10];
int rzeros[N];
int czeros[N];
int cols[N][10];
int coord[N][10];
int num = 0;

int values[9][9] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
};

int solve(int);

int main()
{
    time_t now = clock();

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

            rzeros[i] += grid[i][j] == 0;
            czeros[j] += grid[i][j] == 0;
        }
    }

    stable_sort(pos.begin(), pos.begin() + num, [](const vector<int> &p1, const vector<int> &p2) {
        // return rzeros[p1[0]] + czeros[p1[1]] < rzeros[p2[0]] + czeros[p2[1]];
        return rzeros[p1[0]] < rzeros[p2[0]];
    });

    int cost = solve(0);

    printf("%d\n", cost);

    return 0;
}

int solve(int step)
{
    int cost = 0;

    if (step == num)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                cost += grid[i][j] * values[i][j];
        return cost;
    }

    int i = pos[step][0];
    int j = pos[step][1];

    cost = -1;

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
        cost = max(cost, solve(step + 1));
        rows[i][n] = 0;
        cols[j][n] = 0;
        coord[g][n] = 0;
        grid[i][j] = 0;
    }

    return cost;
}