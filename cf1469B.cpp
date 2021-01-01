#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 110;

int main()
{
    int t, n, m, v;
    cin >> t;

    while (t--)
    {
        cin >> n;
        int sum1 = 0, sum2 = 0, ans1 = 0, ans2 = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> v;
            sum1 += v;
            ans1 = max(ans1, sum1);
        }

        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> v;
            sum2 += v;
            ans2 = max(ans2, sum2);
        }
        cout << max(0, ans1 + ans2) << endl;
    }

    return 0;
}