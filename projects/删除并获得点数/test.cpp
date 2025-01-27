#include <vector>

using namespace std;

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int n = nums.size();
        int maxNum = 0;
        for (int i = 0; i < n; i++) {
            maxNum = max(maxNum, nums[i]);
        }
        // 设置rob的数组
        vector<int> robs(maxNum+1, 0);
        for (int i = 0; i < n; i++) {
            robs[nums[i]] += nums[i];
        }
        // 设置dp数组
        vector<int> f(maxNum+1);
        f[0] = 0; f[1] = robs[1];
        for (int i = 2; i <= maxNum; i++) {
            f[i] = max(f[i-1], robs[i] + f[i-2]);
        }
        return f[maxNum];
    }
};
