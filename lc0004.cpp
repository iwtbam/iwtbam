class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int ns1 = nums1.size();
        int ns2 = nums2.size();
        int left = (ns1 + ns2 + 1) / 2;
        int right = (ns1 + ns2 + 2) / 2;
        return (findKth(nums1, 0, nums2, 0, left) + findKth(nums1, 0, nums2, 0, right)) / 2.0;
    }

    double findKth(const vector<int>& nums1, int s1, const vector<int>& nums2, int s2, int k){
        if(s1 >= nums1.size())
            return nums2[s2 + k - 1];

        if(s2 >= nums2.size())
            return nums1[s1 + k - 1];
        
        if(k == 1)
            return min(nums1[s1], nums2[s2]);

        int hk = k / 2;
        int mid1 = s1 + hk - 1 < nums1.size() ? nums1[s1 + hk - 1] : INT_MAX;
        int mid2 = s2 + hk - 1 < nums2.size() ? nums2[s2 + hk - 1] : INT_MAX;
        if(mid1 < mid2)
            return findKth(nums1, s1 + hk, nums2, s2, k - hk);
        return findKth(nums1, s1, nums2, s2 + hk, k - hk);
    }
};