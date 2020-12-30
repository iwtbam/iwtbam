#include <cstdio>
#include <string>
#include <algorithm>
#include <cstring>

using std::sort;
using std::string;
using std::unique;

const int MAXN = 1e5 + 10;

struct Relation
{
    long long var1, var2;
};

Relation relations[2][MAXN];
int size[2] = {0, 0};

long long nums[MAXN * 2];
long long nodes[MAXN * 2];
long long rank[MAXN * 2];

int bin_search(int l, int r, long long target);
inline int parent(int x);
bool merge(int x, int y);
void init(int e);

int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {

        scanf("%d", &n);
        long long l, r, ans;

        size[0] = 0;
        size[1] = 0;

        for (int i = 0; i < n; i++)
        {
            scanf("%lld%lld%lld", &l, &r, &ans);
            nums[i * 2] = l;
            nums[i * 2 + 1] = r;

            relations[ans][size[ans]].var1 = l;
            relations[ans][size[ans]].var2 = r;
            ++size[ans];
        }

        sort(nums, nums + 2 * n);
        auto e = unique(nums, nums + 2 * n) - nums;

        init(e);

        for (int i = 0; i < size[1]; i++)
        {
            int x1 = bin_search(0, e - 1, relations[1][i].var1);
            int x2 = bin_search(0, e - 1, relations[1][i].var2);
            merge(x1, x2);
        }

        string res = "YES";
        for (int i = 0; i < size[0]; i++)
        {
            int x1 = bin_search(0, e - 1, relations[0][i].var1);
            int x2 = bin_search(0, e - 1, relations[0][i].var2);
            if (parent(x1) == parent(x2))
            {
                res = "NO";
                break;
            }
        }

        printf("%s\n", res.c_str());
    }

    return 0;
}

void init(int e)
{
    for (int i = 0; i < e; i++)
        nodes[i] = i;
    memset(rank, 0, sizeof(rank));
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

inline int parent(int x)
{
    return nodes[x] == x ? x : parent(nodes[x]);
}

bool merge(int x, int y)
{
    int fx = parent(x);
    int fy = parent(y);

    if (fx == fy)
        return false;

    if (rank[fx] < rank[fy])
        nodes[fx] = fy;
    else
    {
        if (rank[fx] == rank[fy])
            rank[fx]++;
        nodes[fy] = fx;
    }
    return true;
}