#include<vector>
#include <numeric>

using namespace std;

// 暴力解法：记录所有的划分可能，判断是不是能划分
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int totSum = accumulate(nums.begin(), nums.end(), 0);
        float halfSum = totSum/2.0;
        int startIdx = -1;
        bool res = false;
        searchPartition(halfSum, startIdx, 0, nums, res);
        return res;
    }

    void searchPartition(float halfSum, int currIdx, int currSum, vector<int>& nums, bool& res) {
        if (currSum > halfSum) return;
        if (currSum == halfSum) {
            res = true;
            return;
        }
        int i = currIdx+1;
        if (i == nums.size()) return;
        // 记录两种情况：
        currSum += nums[i];
        searchPartition(halfSum, i, currSum, nums, res);
        if (res) return;
        currSum -= nums[i];
        searchPartition(halfSum, i, currSum, nums, res);
        if (res) return;
    }
};

// 动态规划：
class Solution2 {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(),0), n = nums.size();
        if (sum % 2 != 0) return false;
        if (n < 2) return false;
        int halfSum = sum / 2;
        vector<vector<bool>> d = vector<vector<bool>>(n, vector<bool>(halfSum + 1, false));
        // 初始化第一列为true、d[i][nums[i]]为true
        for (int i = 0; i <n; i++) {
            d[i][0] = true;
            if (nums[i] <= halfSum) d[i][nums[i]] = true;
        }
        // 进行dp转移：d[i][j] = d[i-1][j-nums[i]] || d[i-1][j]
        for (int i = 0; i < n; i++) {
            for (int j = halfSum; j >= nums[i]; j--) {
                d[i][j] = d[i-1][j-nums[i]] || d[i-1][j];
            }
            if (d[i][halfSum]) return true;
            for (int j = 0; j < nums[i]; j++) {
                d[i][j] = d[i-1][j];
            }
        }
        return false;
    }
};

// 动态规划：空间优化
class Solution3 {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(),0), n = nums.size();
        int maxNum = *max_element(nums.begin(), nums.end());
        int halfSum = sum / 2;
        if (sum % 2 != 0 || maxNum > halfSum) return false;
        if (n < 2) return false;
        vector<bool> d(halfSum+1, false);
        // 初始化第一列为true、d[i][nums[i]]为true
        d[0] = true;
        if (nums[0] <= halfSum) d[nums[0]] = true;
        // 进行dp转移：d[i][j] = d[i-1][j-nums[i]] || d[i-1][j]
        for (int i = 1; i < n; i++) {
            for (int j = halfSum; j >= nums[i]; j--) {
                d[j] = d[j-nums[i]] || d[j];
            }
            if (d[halfSum]) return true;
        }
        return false;
    }
};
