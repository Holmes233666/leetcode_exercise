#include<vector>

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        // 处理特殊情况
        int n = nums.size();
        if (n == 0) return {};
        vector<string> res;

        int left = 0, right = 0;
        while (right < n) {
            right = left + 1;
            while (right < n &&
                   nums[right] == nums[right - 1] + 1) { // 比前一个数字刚好大1
                right++;
                   }
            if (right == left + 1) { // 这个区间只有left一个数
                res.push_back(to_string(nums[left]));
            } else { // 从left->right-1构成一个区间
                res.push_back(to_string(nums[left]) + "->" +
                              to_string(nums[right - 1]));
            }
            left = right;
        }
        return res;
    }
};