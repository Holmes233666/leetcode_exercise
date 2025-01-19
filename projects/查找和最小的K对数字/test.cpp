#include<vector>
#include<set>
#include<queue>

using namespace std;

// 法1：堆 + 使用标记数组
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(), m = nums2.size();
        // 使用 lambda 表达式捕获 nums1 和 nums2
        auto cmp = [&nums1, &nums2](const vector<int>& a1, const vector<int>& a2) {
            return nums1[a1[0]] + nums2[a1[1]] > nums1[a2[0]] + nums2[a2[1]]; // 小顶堆
        };

        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        vector<vector<int>> res;
        set<pair<int, int>> has_pushed;

        pq.emplace(vector<int>{0, 0});
        has_pushed.insert({0,0});
        int currNum = 0;

        while (!pq.empty() && currNum < k) {
            vector<int> currMinIdx = pq.top();
            pq.pop();
            res.push_back({nums1[currMinIdx[0]], nums2[currMinIdx[1]]});
            int nextidx1_1 = currMinIdx[0] + 1, nextidx1_2 = currMinIdx[1];
            if (nextidx1_1 < n && has_pushed.find({nextidx1_1, nextidx1_2}) == has_pushed.end()) {
                pq.emplace(vector<int>{nextidx1_1, nextidx1_2});
                has_pushed.insert({nextidx1_1, nextidx1_2});
            }
            int nextidx2_1 = currMinIdx[0], nextidx2_2 = currMinIdx[1] + 1;
            if (nextidx2_2 < m && has_pushed.find({nextidx2_1, nextidx2_2}) == has_pushed.end()) {
                pq.emplace(vector<int>{nextidx2_1, nextidx2_2});
                has_pushed.insert({nextidx2_1, nextidx2_2});
            }
            currNum++;
        }
        return res;
    }
};

// 法2： 使用堆，但不加标记数组
class Solution2 {
public:
    struct cmp {
        bool operator()(vector<int>& a1, vector<int>& a2) {
            return a1[0] > a2[0];
        }
    };
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(), m = nums2.size();
        priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
        vector<vector<int>> res;
        pq.emplace(vector<int>{0, 0, 0});
        int currNum = 0;

        // 首先将(0,0), (0,1), (0,2), ..., (0,m)加入堆中
        for (int j = 0; j < m; j++) {
            pq.emplace(vector<int>{nums1[0]+nums2[j], 0, j});
        }

        // 弹出pq，每次再选择最小的一个压入
        while (!pq.empty() && currNum < k) {
            vector<int> currMin = pq.top();
            pq.pop();
            res.push_back({nums1[currMin[1]], nums2[currMin[2]]});
            int nexti = currMin[1]+1, nextj = currMin[2];
            pq.emplace(vector<int>{nums1[nexti]+nums2[nextj], nexti, nextj});
            currNum++;
        }
        return res;
    }
};
