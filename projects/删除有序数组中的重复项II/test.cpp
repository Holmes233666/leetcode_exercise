#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0, fast = 0, n = nums.size();
        while (fast < n) {
            int temp = nums[fast];
            int steps = 0;
            while(fast < n && nums[fast] == temp) { // 找到第一个与当前下标不同的元素
                fast++;
                steps++;
            }
            nums[slow] = nums[fast-1];
            if (steps) {    // 不止一个数，那么保留两个
                nums[slow+1] = nums[slow];
                slow += 2;
            }else {
                slow++;
            }
        }
        return slow;
    }
};
