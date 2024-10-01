#include<vector>

using namespace std;

// 暴力解法
class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> ifJump = vector<bool>(nums.size(), false);
        ifJump[0] = true;
        for (int i = 0; i < nums.size(); i++) {
            if (ifJump[i]) {
                for (int j = 1; j < nums[i]; j++) {
                    ifJump[i+j] = true;
                }
            }
        }
        return ifJump[nums.size()-1];
    }
};

// 在2的基础上提前跳出循环即可
class Solution2 {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> ifJump = vector<bool>(nums.size(), false);
        ifJump[0] = true;
        int lastMaxIdx = 0;
        for (int i = 0; i < nums.size(); i++) {
            int maxStepIdx = i + nums[i] >= nums.size() ? nums.size()-1 : i + nums[i];
            if (ifJump[i] || lastMaxIdx > i) {
                ifJump[maxStepIdx] = true;
                lastMaxIdx = max(maxStepIdx, lastMaxIdx);
                if (lastMaxIdx >= nums.size()-1) return true;   // 提前跳出循环的重要性
            }
        }
        return false;
    }
};

// solution2 基础上进行简化，减少不必要的过程
// 核心：记录走到的最大的位置
class Solution3 {
public:
    bool canJump(vector<int>& nums) {
        int lastMaxIdx = nums[0];
        for (int i = 0; i <= lastMaxIdx; i++) {
            lastMaxIdx = max(i + nums[i], lastMaxIdx);
            if (lastMaxIdx >= nums.size()-1) return true;   // 提前跳出循环的重要性
        }
        return false;
    }
};