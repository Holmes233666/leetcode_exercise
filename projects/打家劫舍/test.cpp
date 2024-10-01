#include<vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n==1) return nums[0];
        vector<vector<int>> f = vector<vector<int>>(2, vector<int>(n, 0));  // 2个数组，0是不取，1是取
        f[0][0] = 0;    // 对于第0家，不取
        f[1][0] = nums[0];  // 对于第0家，取
        f[0][1] = nums[0];  // 对于第1家，不取
        f[1][1] = nums[1];  // 对于第1家，取
        int maxPro = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            f[0][i] = max(max(f[0][i-1], f[1][i-1]), max(f[0][i-2], f[1][i-2]));
            f[1][i] = max(f[0][i-2], f[1][i-2]) + nums[i];
            maxPro = max(f[0][i], f[1][i]);
        }
        return maxPro;
    }
};


class Solution2 {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n==1) return nums[0];
        vector<int> f = vector<int>(n, nums[0]);
        f[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            f[i] = max(f[i-2] + nums[i], f[i-1]);
        }
        return f[n-1];
    }
};