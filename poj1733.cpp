#include <cstdio>
#include <algorithm>

using std::sort;
using std::unique;

const int N = 10001;
int node[N * 2];
long long nums[N * 2];

void init(int size);
int get(int x);
bool merge(int x, int y);
int bin_search(int l, int r, long long target);

struct Query
{
    long long n1, n2;
    int ans;
};

Query query[N];

int main()
{
    long long n, m;
    char s[5];
    scanf("%lld %lld", &n, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%lld %lld %s", &query[i].n1, &query[i].n2, s);
        query[i].ans = s[0] == 'e' ? 0 : 1;
        nums[i * 2] = query[i].n1 - 1;
        nums[i * 2 + 1] = query[i].n2;
    }

    sort(nums, nums + 2 * m);
    int size = unique(nums, nums + 2 * m) - nums;

    init(size * 2);
    for (int i = 0; i < m; i++)
    {
        int x = bin_search(0, size - 1, query[i].n1 - 1);
        int y = bin_search(0, size - 1, query[i].n2);

        if (query[i].ans == 0)
        {
            if (get(x) == get(y + size))
            {
                printf("%d\n", i);
                break;
            }

            merge(x, y);
            merge(x + size, y + size);
        }
        else
        {
            if (get(x) == get(y))
            {
                printf("%d\n", i);
                break;
            }
            merge(x + size, y);
            merge(x, y + size);
        }
    }

    return 0;
}

void init(int size)
{
    for (int i = 0; i < size; i++)
        node[i] = i;
}

int get(int x)
{
    if (node[x] == x)
        return x;
    return node[x] = get(node[x]);
}

bool merge(int x, int y)
{
    int fx = get(x), fy = get(y);
    if (fx == fy)
        return false;
    node[fx] = fy;
    return true;
}

int bin_search(int l, int r, long long target)
{
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (nums[mid] >= target)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}