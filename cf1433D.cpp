#include <cstdio>

const int MAX_NUM = 5001;

int nums[MAX_NUM];

int main()
{
    int n, m;
    scanf("%d", &n);
    while (n--)
    {
        int diff = -1;

        scanf("%d", &m);
        scanf("%d", &nums[0]);

        for (int i = 1; i < m; i++)
        {
            scanf("%d", &nums[i]);
            if (diff == -1 && nums[i] != nums[0])
                diff = i;
        }

        if (diff < 0)
        {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        for (int i = 1; i < m; i++)
        {
            if (nums[i] == nums[0])
                printf("%d %d\n", diff + 1, i + 1);
            else
                printf("%d %d\n", 1, i + 1);
        }
    }

    return 0;
}