#include <iostream>
#include <vector>
#include <cmath>

using std::ceil;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

const int MAXN = 20;

bool solve(vector<int> books, int step, int k);
int f(const vector<int> &books);
void to(const vector<int> &books, vector<int> &next, int i, int j, int p);

int main()
{
    int T, N;
    cin >> T;
    while (T--)
    {
        cin >> N;
        vector<int> books(N, 0);
        for (int i = 0; i < N; i++)
            cin >> books[i];

        int step = 1;

        if (f(books) == 0)
        {
            cout << 0 << endl;
            continue;
        }

        while (step < 5)
        {
            if (solve(books, 0, step))
                break;
            step++;
        }

        if (step >= 5)
            cout << "5 or more" << endl;
        else
            cout << step << endl;
    }

    return 0;
}

bool solve(vector<int> books, int step, int k)
{
    int error = f(books);

    if (step + error > k)
        return false;

    if (error == 0)
        return true;

    size_t size = books.size();

    vector<int> next(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            for (int p = 0; p <= i - 1; p++)
            {
                to(books, next, i, j, p);
                error = f(next);
                if (error + step + 1 <= k && solve(next, step + 1, k))
                    return true;
            }
        }
    }

    return false;
}

void to(const vector<int> &books, vector<int> &next, int i, int j, int k)
{
    int cur = 0;
    for (int p = 0; p < k; p++)
        next[cur++] = books[p];

    for (int p = i; p < j + 1; p++)
        next[cur++] = books[p];

    for (int p = k; p < i; p++)
        next[cur++] = books[p];

    for (int p = j + 1; p < books.size(); p++)
        next[cur++] = books[p];
}

int f(const vector<int> &books)
{
    int size = books.size(), tot = 0;
    for (int i = 0; i < size - 1; i++)
        if (books[i + 1] != books[i] + 1)
            tot++;
    return ceil(tot / 3.0);
}