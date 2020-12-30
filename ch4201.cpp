#include <cstdio>
#include <cstring>

const int MAXN = 2e5 + 10;

enum Sign
{
    GT = 0, // 大于
    LT = 1  // 小于
};

int tree[MAXN];
int nums[MAXN];
int left[2][MAXN];
int right[2][MAXN];

int n;

void add(int i, int x);
int ask(int i);

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    for (int i = 1; i <= n; i++)
    {
        left[LT][i] = ask(nums[i] - 1);
        left[GT][i] = i - 1 - ask(nums[i]);
        add(nums[i], 1);
    }

    memset(tree, 0, (n + 1) * sizeof(int));

    for (int i = n; i >= 1; i--)
    {
        right[LT][i] = ask(nums[i] - 1);
        right[GT][i] = (n - i) - ask(nums[i]);
        add(nums[i], 1);
    }

    long long s1 = 0, s2 = 0;

    for (int i = 1; i <= n; i++)
    {
        s1 += left[LT][i] * right[LT][i];
        s2 += left[GT][i] * right[GT][i];
    }

    printf("%lld %lld\n", s1, s2);
    return 0;
}

void add(int i, int x)
{
    while (i <= n)
    {
        tree[i] += x;
        i += i & (-i);
    }
}

int ask(int i)
{
    int sum = 0;
    while (i > 0)
    {
        sum += tree[i];
        i -= i & (-i);
    }
    return sum;
}
