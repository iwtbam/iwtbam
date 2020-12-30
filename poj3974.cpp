#include <vector>
#include <iostream>
#include <string>

using namespace std;

const int P = 131;

using ull = unsigned long long;

int bin_search(int pos, const vector<ull> &hash, const vector<ull> &ps,
               const vector<ull> &rev_hash, const vector<ull> &rev_ps)
{
    int l = 0, r = pos;
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (pos[l])
    }
}

int main()
{
    string s;
    cin >> s;

    size_t size = s.size();

    vector<ull> hash(size + 1, 0), ps(size + 1, 1);
    vector<ull> rev_hash(size + 2, 0), rev_ps(size + 2, 1);

    for (int i = 1; i <= size; i++)
    {
        hash[i] = hash[i - 1] * P + s[i - 1];
        ps[i] = ps[i - 1] * P;
        rev_hash[size - i + 1] = rev_hash[size - i + 2] + s[size - i];
        rev_ps[size - i + 1] = rev_ps[size - i + 2] * P;
    }

    int res = 0;
    for (int i = 0; i < size; i++)
    {
    }
}