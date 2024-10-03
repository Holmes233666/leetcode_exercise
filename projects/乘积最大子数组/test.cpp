#include<vector>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // vector<int> f = vector<int>(nums.size(), -LONG_MAX);
        vector<int> maxVec = vector<int>(nums.size(), -INT_MAX);
        vector<int> minVec = vector<int>(nums.size(), INT_MAX);
        vector<vector<int>> f;
        f.push_back(maxVec);
        f.push_back(minVec);
        f[0][0] = nums[0];  // 第一个0表示到i的最大乘积子数组的最大值
        f[1][0] = nums[0];  // 第一个1表示到i的最大乘积子数组的最小值
        int res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            f[0][i] = max(max(nums[i], f[0][i-1]*nums[i]), max(nums[i], f[1][i-1]*nums[i]));
            f[1][i] = min(min(nums[i], f[0][i-1]*nums[i]), min(nums[i], f[1][i-1]*nums[i]));
            res = max(max(res, f[0][i]), max(res, f[1][i]));
        }
        return res;
    }
};

class Solution2 {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> maxVec(nums.begin(), nums.end()), minVec = vector<int>(nums.begin(), nums.end());
        vector<vector<int>> f;
        int res = nums[0];
        f.push_back(maxVec);
        f.push_back(minVec);
        for (int i = 1; i < nums.size(); i++) {
            f[0][i] = max(max(nums[i], f[0][i-1]*nums[i]), max(nums[i], f[1][i-1]*nums[i]));
            f[1][i] = min(min(nums[i], f[0][i-1]*nums[i]), min(nums[i], f[1][i-1]*nums[i]));
            res = max(max(res, f[0][i]), max(res, f[1][i]));
        }
        return res;
    }
};