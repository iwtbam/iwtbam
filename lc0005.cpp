class Solution {
public:
    string longestPalindrome(string s) {
        string pre = "#";
        size_t size = s.size();
        for(int i = 0 ; i < size ; i++){
            pre.push_back(s[i]);
            pre.push_back('#');
        }

        vector<int> arm_lens = {};
        size = pre.size();

        int right = -1, j = -1, min_arm_len, cur_arm_len;

        for(int i = 0; i < size; i++){
            if(right >= i){
                int i_sym = 2 * j - i;
                min_arm_len = min(arm_lens[i_sym], right - i);
                cur_arm_len = expand(pre, i - min_arm_len, i + min_arm_len);
            }else{
                cur_arm_len = expand(pre, i, i);
            }

            arm_lens.push_back(cur_arm_len);
            
            if(i + cur_arm_len > right) {
                j = i;
                right = i + cur_arm_len;
            }
        }    

        int pos = max_element(arm_lens.begin(), arm_lens.end()) - arm_lens.begin();
        int arm_len = arm_lens[pos];

        string res = {};
        for(int i =  pos - arm_len; i <= pos + arm_len; i++){
            if(pre[i] != '#')
                res.push_back(pre[i]);
        }
        return res;
    }

    int expand(const string& s, int left, int right){
        size_t size = s.size();
        while(left >= 0 && right < size && s[left] == s[right]){
            left -= 1;
            right += 1;
        }
        return (right - left  - 2) / 2;
    }
};