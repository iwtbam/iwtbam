#include <iostream>
using namespace std;

const int N = 600010;

int trie[N * 24][2], lasted[N * 24];
int s[N], root[N], n, m, tot;

void insert(int i, int k, int p, int q)
{
    if (k < 0)
    {
        lasted[q] = i;
        return;
    }

    int c = s[i] >> k & 1;
    if (p)
        trie[q][c ^ 1] = trie[p][c ^ 1];
    trie[q][c] = ++tot;
    insert(i, k - 1, trie[p][c], trie[q][c]);
    lasted[q] = max(lasted[trie[q][0]], lasted[trie[q][1]]);
}

int ask(int now, int val, int k, int limit)
{
    if (k < 0)
        return s[lasted[now]] ^ val;
    int c = val >> k & 1;
    if (lasted[trie[now][c ^ 1]] >= limit)
        return ask(trie[now][c ^ 1], val, k - 1, limit);
    else
        return ask(trie[now][c], val, k - 1, limit);
}

int main()
{
    cin >> n >> m;
    lasted[0] = -1;
    root[0] = ++tot;
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        s[i] = s[i - 1] ^ x;
        root[i] = ++tot;
        insert(i, 23, root[i - 1], root[i]);
    }

    for (int i = 1; i <= m; i++)
    {
        char op[2];
        scanf("%s", op);
        if (op[0] == 'A')
        {
            int x;
            scanf("%d", &x);
            root[++n] = ++tot;
            s[n] = s[n - 1] ^ x;
            insert(n, 23, root[n - 1], root[n]);
        }
        else
        {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            printf("%d\n", ask(root[r - 1], x ^ s[n], 23, l - 1));
        }
    }
    return 0;
}