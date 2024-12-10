#include<vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size(), i = 0;
        int newStart = newInterval[0], newEnd = newInterval[1];
        vector<vector<int>> res;

        // 首先在区间序列中找到记录第一个不满足的区间newStartIdx，其他的入vector
        for (; i < n && newStart > intervals[i][1]; i++) {
            res.push_back(intervals[i]);
        }

        // 处理重叠的区间
        for (; i < n && newEnd >= intervals[i][0]; i++) {
            newStart = min(intervals[i][0], newStart);
            newEnd = max(intervals[i][1], newEnd);
        }
        res.push_back({newStart, newEnd});

        // 其他的区间一次放入
        for (; i < n; i++) {
            res.push_back(intervals[i]);
        }
        return res;
    }
};
