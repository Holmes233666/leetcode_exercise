#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // 首先对数组进行排序
        sort(candidates.begin(), candidates.end());
        // 进行深搜，寻找满足target的组合：
        vector<int> currRes;
        DFS(candidates, currRes, 0, 0, target);
        return res;
    }

    void DFS(vector<int>& candidates, vector<int>& currRes, int currIndex, int currSum, int target) {
        // 满足递归条件，递归终止
        if (currSum == target) {
            res.push_back(currRes);
            return;
        }
        // 可能满足条件，继续深搜
        for (int i = currIndex; i < candidates.size(); i++) {
            // 当前轮次不用深搜 i 之后的数值
            if (currSum + candidates[i] > target) {
                return;
            }
            // 可以尝试
            currSum += candidates[i];
            currRes.push_back(candidates[i]);
            DFS(candidates, currRes, i, currSum, target);
            currRes.pop_back();
            currSum -= candidates[i];
        }
    }
};
