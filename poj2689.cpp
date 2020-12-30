#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::sqrt;
using std::string;
using std::to_string;

const long long maxn = 1e6 + 100;
long long primers[maxn], tot;
int bk[maxn];

string solve(long long L, long long U);

void init()
{
    for (long long i = 2; i < maxn; i++)
    {
        if (bk[i])
            continue;
        primers[tot++] = i;
        for (long long j = 2; i * j < maxn; j++)
            bk[i * j] = 1;
    }
}

int main()
{
    long long L, U;
    init();
    while (cin >> L >> U)
    {
        cout << solve(L, U) << endl;
    }
}

string solve(long long L, long long U)
{
    memset(bk, 0, sizeof(bk));
    int upper = sqrt(U);
    for (long long i = 0; i < tot; i++)
    {
        if (primers[i] > upper)
            continue;

        int lb = max(2LL, L / primers[i]);
        int ub = U / primers[i];
        for (int j = lb; j <= ub; j++)
            bk[primers[i] * j - L] = 1;
    }

    long long min_dis = 0x3f3f3f3f, max_dis = 0;
    long long l = -1, minl = -1, minr = -1, maxl = -1, maxr = -1;
    for (long long i = max(2LL, L); i <= U; i++)
    {
        if (bk[i - L] == 0)
        {
            if (l != -1)
            {
                if (i - l < min_dis)
                {
                    minl = l;
                    minr = i;
                    min_dis = i - l;
                }

                if (i - l > max_dis)
                {
                    maxl = l;
                    maxr = i;
                    max_dis = i - l;
                }
            }
            l = i;
        }
    }

    if (minr == -1)
        return "There are no adjacent primes.";
    return to_string(minl) + "," + to_string(minr) + " are closest, " + to_string(maxl) + "," + to_string(maxr) + " are most distant.";
}
