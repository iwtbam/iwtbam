#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>

using std::ceil;
using std::cin;
using std::cout;
using std::endl;
using std::lower_bound;
using std::min;
using std::sort;
using std::sqrt;
using std::swap;
using std::unique;

const int N = 40000 + 100;
const int T = 37;
int record[N], data[N], data2[N], map[N];
int count[T][T][N];
int res[N];

int t, L, cnt, n, m, x = 0;

void build()
{
    for (int i = 0; i < n; i++)
        count[i / L][i / L][map[i]]++;

    int len = n / L + (n % L != 0);

    for (int i = 0; i < len - 1; i++)
        for (int j = i + 1; j < len; j++)
            for (int k = 0; k < cnt; k++)
                count[i][j][k] = count[i][j - 1][k] + count[j][j][k];
}

int ask(int l, int r)
{
    int p = l / L;
    int q = r / L;

    memset(res, 0, sizeof(res));

    if (p == q)
    {
        for (int i = l; i <= r; i++)
            res[map[i]] += 1;
    }
    else
    {
        for (int i = l; i < p * L + L && i < n; i++)
            res[map[i]] += 1;

        if (p + 1 <= q - 1)
        {
            for (int i = 0; i < cnt; i++)
                res[i] += count[p + 1][q - 1][i];
        }

        for (int i = q * L; i <= r; i++)
            res[map[i]] += 1;
    }

    int ans = 0;

    for (int i = 0; i < cnt; i++)
        if (res[i] > res[ans])
            ans = i;

    return data2[ans];
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> data[i];
        data2[i] = data[i];
    }

    t = ceil(pow(n, 1.0 / 3));
    L = n / t;

    sort(data2, data2 + n);
    cnt = unique(data2, data2 + n) - data2;

    for (int i = 0; i < n; i++)
        map[i] = lower_bound(data2, data2 + cnt, data[i]) - data2;
    build();
    long long l, r;

    for (int i = 0; i < m; i++)
    {
        cin >> l >> r;
        l = (l + x - 1) % n + 1;
        r = (r + x - 1) % n + 1;

        if (l > r)
            swap(l, r);
        x = ask(l - 1, r - 1);
        cout << x << endl;
    }

    return 0;
}
