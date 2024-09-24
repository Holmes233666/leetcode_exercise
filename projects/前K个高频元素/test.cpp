#include<vector>
#include<unordered_map>
#include<queue>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> umap;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            umap[nums[i]]++;
        }
        // 将umap中的元素转换为pair，放到堆中进行排序
        priority_queue<pair<int,int>, Compare> pq;
        for (auto it = umap.begin(); it != umap.end(); it++) {
            pq.push({it->first, it->second});
        }
        // 弹出其中的元素放入
        while (k--) {
            res.push_back(pq.top.second);
            pq.pop();
        }
        return res;
    }

    struct Compare {
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
            // 以pair的second元素为基准进行比较
            return a.second < b.second; // a的second小于b的second，则a优先级低
        }
    };
};

