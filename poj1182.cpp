#include <cstdio>

const int MAXN = 50001;
int node[MAXN * 3];

int get(int x);

int main()
{
    int n, m, l, r, ans, fake = 0;
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= 3 * n; i++)
        node[i] = i;

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &ans, &l, &r);
        if (l < 1 || l > n || r < 1 || r > n)
        {
            fake++;
            continue;
        }

        if (ans == 1)
        {
            if (get(l + n) == get(r) || get(l) == get(r + n))
            {
                fake++;
                continue;
            }

            node[get(l)] = get(r);
            node[get(l + n)] = get(r + n);
            node[get(l + 2 * n)] = get(r + 2 * n);
        }
        else
        {
            if (get(l) == get(r) || get(l) == get(r + n))
            {
                fake++;
                continue;
            }

            node[get(l + n)] = get(r);
            node[get(l + 2 * n)] = get(r + n);
            node[get(l)] = get(r * n * 2);
        }
    }

    printf("%d\n", fake);
    return 0;
}

int get(int x)
{
    if (node[x] == x)
        return x;
    return node[x] = get(node[x]);
}