#include<vector>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), maxLen = 1;
        vector<int> f(n, 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    f[i] = max(f[i], f[j]+1);
                    maxLen = max(f[i], maxLen);
                }
            }
        }
        return maxLen;
    }
};