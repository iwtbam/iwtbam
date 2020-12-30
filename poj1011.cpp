#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int a[100], v[100], len, cnt, n;

bool dfs(int stick, int cap, int last)
{
    if (stick > cnt)
        return true;
    if (cap == len)
        return dfs(stick + 1, 0, 1);

    int fail = 0;
    for (int i = last; i <= n; i++)
    {
        if (v[i] || cap + a[i] > len || fail == a[i])
            continue;

        v[i] = 1;
        if (dfs(stick, cap + a[i], i + 1))
            return true;
        fail = a[i];
        v[i] = 0;
        if (cap == 0 || cap + a[i] == len)
            return false;
    }
    return false;
}

int main()
{
    while (cin >> n && n != 0)
    {
        int sum = 0, val = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            sum += a[i];
            val = max(a[i], val);
        }
        sort(a + 1, a + n + 1);
        reverse(a + 1, a + n + 1);
        for (len = val; len < sum; len++)
        {
            if (sum % len)
                continue;
            memset(v, 0, sizeof(v));
            cnt = sum / len;
            if (dfs(1, 0, 1))
            {
                break;
            }
        }
        cout << len << endl;
    }
    return 0;
}