#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int N;

const int MAXN = 1e6 + 1;

int primers[MAXN];
int vis[MAXN];
int tot = 0;

void init(int N);

int main()
{
    int N;
    cin >> N;
    init(N);

    for (int i = 0; i < tot; i++)
    {
        int num = 0;
        int base = primers[i];
        while (base <= N)
        {
            num += N / base;
            base *= primers[i];
        }

        if (num > 0)
            cout << primers[i] << " " << num << endl;
    }

    return 0;
}

void init(int N)
{
    for (int i = 2; i <= N; i++)
    {
        if (vis[i] == 0)
        {
            vis[i] = i;
            primers[tot++] = i;
        }

        for (int j = 0; j < tot; j++)
        {
            if (primers[j] > i || primers[j] * i > N)
                break;
            vis[primers[j] * i] = primers[j];
        }
    }
}