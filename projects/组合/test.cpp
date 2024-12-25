#include<vector>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> nums(n);
        vector<int> tempVec;
        vector<vector<int>> res;
        iota(nums.begin(), nums.end(), 1);
        dfs(res, tempVec, nums, k, -1);
        return res;
    }

    void dfs(vector<vector<int>>& res, vector<int>& currRes, vector<int>& nums, int k, int idx) {
        if (k == currRes.size()) {
            res.push_back(currRes);
            return;
        }
        // 如果当前还需要放数且可以放数，那么判断后面这些数放哪个
        for (int i = idx+1; i < nums.size(); i++) {
            currRes.push_back(nums[i]);
            dfs(res, currRes, nums, k, i);
            currRes.pop_back();
        }
        // 如果已经不能放数了，直接返回
    }
};
