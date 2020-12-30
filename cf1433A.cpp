#include <cstdio>

int record[5] = {0, 1, 3, 6, 10};

inline count(int num);
int main()
{
    int n, num;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &num);
        printf("%d\n", ((num % 10) - 1) * 10 + record[count(num)]);
    }
    return 0;
}

inline count(int num)
{
    int ans = 0;
    while (num > 0)
    {
        num /= 10;
        ans++;
    }
    return ans;
}
