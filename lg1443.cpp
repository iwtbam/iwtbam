#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

using std::pair;
using std::queue;
using std::vector;

const int INF = 0x3f3f3f3f;

const int dxs[8] = {2, 2, -2, -2, 1, 1, -1, -1};
const int dys[8] = {1, -1, 1, -1, 2, -2, 2, -2};

int main()
{
    int rows, cols;
    int x, y;
    scanf("%d%d%d%d", &rows, &cols, &x, &y);

    vector<vector<int>> board(rows, vector<int>(cols, -1));

    queue<pair<int, int>> q;

    q.emplace(x - 1, y - 1);

    board[x - 1][y - 1] = 0;

    while (q.size())
    {

        pair<int, int> p = q.front();
        q.pop();

        int cx = p.first, cy = p.second;
        for (int i = 0; i < 8; i++)
        {
            int nx = cx + dxs[i];
            int ny = cy + dys[i];
            if (nx < 0 || nx >= rows || ny < 0 || ny >= cols)
                continue;

            if (board[nx][ny] != -1 && 1 + board[cx][cy] >= board[nx][ny])
                continue;
            board[nx][ny] = board[cx][cy] + 1;
            q.emplace(nx, ny);
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%-5d", board[i][j]);
        printf("\n");
    }

    return 0;
}
