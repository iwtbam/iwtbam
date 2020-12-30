#include <cstdio>
#include <cstring>
#include <cmath>

using std::abs;

const int MAXN = 30001;

int fa[MAXN];
int d[MAXN];
int size[MAXN];

void init();
int get(int x);
bool merge(int x, int y);

int main()
{
    int T, i, j;
    char c[2];
    scanf("%d", &T);
    init();
    while (T--)
    {
        scanf("%s %d %d", c, &i, &j);
        if (c[0] == 'M')
        {
            merge(i, j);
        }
        else if (c[0] == 'C')
        {
            if (get(i) != get(j))
            {
                printf("-1\n");
            }
            else
            {
                int res = abs(d[i] - d[j]) - 1;
                printf("%d\n", res);
            }
        }
    }
    return 0;
}

void init()
{
    memset(d, 0, sizeof(d));
    for (int i = 0; i < MAXN; i++)
    {
        fa[i] = i;
        size[i] = 1;
    }
}

int get(int x)
{
    if (fa[x] == x)
        return x;
    int root = get(fa[x]);
    d[x] += d[fa[x]];
    return fa[x] = root;
}

bool merge(int x, int y)
{
    x = get(x);
    y = get(y);
    if (x == y)
        return false;
    fa[x] = y;
    d[x] = size[y];
    size[y] += size[x];
    return true;
}