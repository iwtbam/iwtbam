#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;

int main()
{
    int n, x;
    scanf("%d", &n);
    scanf("%d", &x);
    map<int, int> s;
    s[x] = 1;
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &x);

        auto nex = s.lower_bound(x);
        auto pre = prev(nex, 1);
        if (nex == s.end())
        {
            printf("%d %d\n", x - pre->first, pre->second);
        }
        else if (nex == s.begin())
        {
            printf("%d %d\n", nex->first - x, nex->second);
        }
        else if (nex->first - x < x - pre->first)
        {
            printf("%d %d\n", nex->first - x, nex->second);
        }
        else
        {
            printf("%d %d\n", x - pre->first, pre->second);
        }
        s[x] = i;
    }
    return 0;
}