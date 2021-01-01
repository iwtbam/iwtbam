#include <iostream>
#include <cstring>
using namespace std;

const int N = 2e5 + 10;

int record[N];

int main()
{
    int t, n;
    cin >> t;

    while (t--)
    {
        cin >> n;
        memset(record, 0, sizeof(record));
        int ans = 0, val;
        for (int i = 0; i < n; i++)
        {
            cin >> val;
            if (record[val] != 0)
                val++;
            if (record[val] != 0)
                continue;
            record[val] = 1;
            ans++;
        }
        cout << ans << endl;
    }
    return 0;
}