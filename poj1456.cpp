#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

using PII = pair<int, int>;

int solve(const vector<PII>& datas, int n){
    priority_queue<int, vector<int>, greater<int>> q;
    size_t size = datas.size();
    int cur_size = 0;
    for(int i = 0; i < size; i++){
        cur_size = max(cur_size, datas[i].first);
        cur_size = min(n, cur_size);
        if(q.size() < cur_size){
            q.push(datas[i].second);
        }else{
            if(datas[i].second > q.top()){
                q.pop();
                q.push(datas[i].second);
            }
        }
    }
    
    int ans = 0;
    while(q.size()){
        ans += q.top();
        q.pop();
    }
    return ans;
}

int main(){
    int n;
    while(cin >> n){
        vector<PII> datas(n);
        for(int i = 0; i < n; i++){
            cin >> datas[i].second >> datas[i].first;
        }
        sort(datas.begin(), datas.end());
        cout << solve(datas, n) << endl;
    }
    
    return 0;
}