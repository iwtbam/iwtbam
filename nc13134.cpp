#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 1;

int l[N], r[N], data[N];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", data + i);

    l[0] = 1, r[n - 1] = 1;
    for (int i = 1; i < n; i++)
        l[i] = (data[i] > data[i - 1] ? l[i - 1] : 0) + 1;
    for (int i = n - 2; i >= 0; i--)
        r[i] = (data[i + 1] > data[i] ? r[i - 1] : 0) + 1;

    int ans = 2;

    for (int i = 1; i < n - 2; i++)
    {
        if (data[i + 1] > data[i - 1])
            ans = max(ans, l[i - 1] + r[i + 1]);
    }

    printf("%d\n", ans);
    return 0;
}