#include<vector>

using namespace std;

// 枚举宽度
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        for (int left = 0; left < heights.size(); left++) {
            if (heights[left] == 0) continue;
            int miniHeight = heights[left];
            res = max(res, heights[left]);
            for (int right = left + 1; right < heights.size(); right++) {
                miniHeight = min(heights[right], miniHeight);
                res = max(miniHeight * (right - left + 1), res);
            }
        }
        return res;
    }
};