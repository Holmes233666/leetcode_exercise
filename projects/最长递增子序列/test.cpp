#include<vector>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> f = vector<int> (nums.size(), 0);
        for (int i = 1; i < nums.size(); i++) {
            f[i] = nums[i] > nums[i-1] ? f[i-1] + 1 : 1;
        }
        return f[nums.size()-1];
    }
};