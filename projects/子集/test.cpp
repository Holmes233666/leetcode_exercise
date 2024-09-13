#include<vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> currRes;
        DFS(-1, nums, currRes, res);
        return res;
    }

    void DFS(int currIndex, vector<int>& nums, vector<int>& currRes, vector<vector<int>>& res) {
        if (currIndex == nums.size()-1) {
            // 最后一个数了，不需要向后枚举
            res.push_back(currRes);
            return;
        }
        // 对于之后的每一个数，都有放入集合和不放入集合两种选择
        currRes.push_back(nums[currIndex+1]);
        DFS(currIndex+1, nums, currRes, res);
        currRes.pop_back();
        DFS(currIndex+1, nums, currRes, res);
    }
};

int main() {
    vector<int> nums = {1,2,3};
    Solution s;
    s.subsets(nums);
    return 0;
}

