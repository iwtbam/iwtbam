class Solution
{
public:
    vector<double> medianSlidingWindow(vector<int> &nums, int k)
    {

        multiset<int> s;

        for (int i = 0; i < k; i++)
            s.insert(nums[i]);

        int i = k;
        size_t size = nums.size();
        auto mid = next(s.begin(), k / 2);
        vector<double> res;
        while (i <= size)
        {
            res.push_back(((*mid) * 1.0 + (*next(mid, k % 2 - 1))) * 0.5);
            if (i == size)
                break;

            s.insert(nums[i]);
            if (nums[i] < *mid)
                mid--;

            if (nums[i - k] <= *mid)
                mid++;

            s.erase(s.lower_bound(nums[i - k]));
            i++;
        }
        return res;
    }
};