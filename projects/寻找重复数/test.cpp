#include<vector>

using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        // 扫描这个数组，如果nums[i] = 1， 那么将nums[1]处的元素进行减去n+1，变为一个负数
        for (int i = 0; i < nums.size(); i++) {
            // 如果当前的数是一个负数，说明下标i处的数已经出现至少一次了，首先尝试还原下原来的数
            int currNum = nums[i];
            if (currNum + n + 1 < 0) {  // 如果还是小于0，说明数字i已经出现两次了，是重复的数，直接返回（不可能等于0
                return i;
            }else if (currNum < 0){ // 加了n+1之后就恢复了正常的数，那么将正确的数处的下标进行翻转
                currNum = currNum + n + 1;
            }
            nums[currNum] = nums[currNum] - n - 1;
        }
        // 处理完然后扫描一遍数组，看看哪个下标位置的数+n+1还是负数，那个下标就是重复的数
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] + n + 1 < 0) return i;
        }
        return 0;
    }
};