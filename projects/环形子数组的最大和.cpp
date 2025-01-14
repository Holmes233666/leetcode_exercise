#include<vector>

using namespace std;

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int maxNum = nums[0], n = nums.size();
        // 第一种情况：计算 0 < i < j < n, 区间[i,j]上的最大子数组和
        vector<int> f(n);
        for (int i = 1; i < n; i++) {
            f[i] = max(nums[i], nums[i] + f[i-1]);
            maxNum = max(maxNum, f[i]);
        }
        // 第二种情况：计算 0 < i < j < n，区间[0, i], [j, n]上的最大子数组和
        // 首先计算区间 0 - i区间上，任意i < n-1 时的最大前缀和
        vector<int> maxPre(n);  // 多算一个
        maxPre[0] = nums[0];
        int preSum = nums[0];
        for (int i = 1; i < n; i++) {
            preSum += nums[i];
            maxPre[i] = max(maxPre[i-1], preSum);
        }
        int endSum = 0;
        for (int j = n-1; j > 0; j++) {
            endSum += nums[j];
            maxNum = max(maxPre[j-1] + endSum, maxNum);
        }
        return maxNum;
    }
};
