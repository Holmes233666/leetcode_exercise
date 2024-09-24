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

class Solution2 {
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