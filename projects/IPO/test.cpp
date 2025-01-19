#include<vector>
#include<queue>

using namespace std;

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<pair<int, int>> arr;
        priority_queue<int> pq;
        int n = profits.size();
        for (int i = 0; i < n; i++) {
            arr.push_back({capital[i], profits[i]});
        }
        sort(arr.begin(), arr.end());   // 升序排列
        int curr = 0;
        for (int i = 0; i < k; i++) {
            while(curr < n && arr[curr].first <= w) {
                pq.emplace(arr[curr].second);
                curr++;
            }
            if (!pq.empty()) {
                w += pq.top();
                pq.pop();
            }else {
                break;
            }
        }
        return w;
    }
};