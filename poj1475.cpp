#include <iostream>
#include <queue>
#include <utility>

using std::cin;
using std::cout;
using std::pair;
using std::queue;

const int MAX_NUM = 21;

struct State
{
    int x, y, dir;
    State(int x, int y, int d) : x(x), y(y), dir(d){};
};

int M,
    N;
int bx, by, tx, ty, hx, hy;

char grid[MAX_NUM][MAX_NUM];

int man[MAX_NUM][MAX_NUM][4];
int box[MAX_NUM][MAX_NUM][4];

int dxs[4] = {0, 0, 1, -1};
int dys[4] = {1, -1, 0, 0};

const int UN_SOLVE = 0x3f3f3f3f;

void input();
void solve();
void expand();

int main()
{
    while (cin >> M >> N)
    {
        input();
    }
}

void solve()
{
    queue<pair<int, int>> q;
    q.emplace(bx, by);

    while (q.)
}

void input()
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 'T')
            {
                tx = i;
                ty = j;
            }
            else if (grid[i][j] == 'S')
            {
                hx = i;
                hx = j;
            }
            else if (grid[i][j] == 'B')
            {
                bx = i;
                by = j;
            }
        }
    }
}
