#include<iostream>
#include<vector>

using namespace std;

// 重复项删除与移除元素类似，都是类似快排中的两个指针pivot操作
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size(), slow = 0, fast = 0;
        while (fast < n) {
            if (nums[slow] == nums[fast]) {
                fast++;
            }else { // 不相等
                slow++;
                nums[slow] = nums[fast];
            }
        }
        return slow+1;
    }
};