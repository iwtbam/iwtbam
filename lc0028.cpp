class Solution {
public:
    int strStr(string haystack, string needle) {
        int ns = needle.size();
        if(ns == 0)
            return 0;
        
        int hs = haystack.size();
        if(hs == 0)
            return -1;

        vector<int> next = build(needle);

        int i = 0, j = 0;
        while(i < hs && j < ns){
            if(j == -1 || haystack[i] == needle[j]){
                i++;
                j++;
            }else{
                j = next[j];
            }
        }

        if(j == ns)
            return i - j;

        return -1;
    }

    vector<int> build(const string& needle){
        size_t ns = needle.size();
        vector<int> next(ns, 0);
        
        next[0] = -1;

        int i = 0, j = -1;

        while(i < ns - 1){
            if(j == -1 || needle[i] == needle[j]){
                ++i;
                ++j;
                next[i] = needle[i] == needle[j] ? next[j] : j;
            }else{
                j = next[j];
            }
        }

        return next;
    }
};