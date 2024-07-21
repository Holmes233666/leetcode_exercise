#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int num_point = 0;
        int zero_point = 0;
        while (zero_point < nums.size() && nums[zero_point] != 0) {
            zero_point++;
        }
        cout <<"零指针: "<<zero_point << endl;
        // 数组中没有0
        if (zero_point == nums.size()) return;
        while (num_point < nums.size()) {
            cout << num_point << endl;
            // 如果数字指针指着零，那么直接右移
            if (nums[num_point] == 0) {
                num_point++; 
                continue;
            }
            // 如果数字指针指着非零，那么需要跟零指针指着的0换一下数值
            if (nums[num_point] != 0 && nums[zero_point] == 0 
            && num_point > zero_point) {
                nums[zero_point] = nums[num_point];
                nums[num_point] = 0;
                // 然后零指针右移，直到遇到第一个零或者越界
                while(zero_point < nums.size() + 1 && nums[zero_point] != 0) {
                    zero_point++;
                }
            }
            // 数组里面的零已经被处理完了
            if (zero_point == nums.size() + 1) {
                break;
            }
            num_point++;
        }
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i] << " ";
        }
    }
};


int main() {
    vector<int> nums = {1};
    Solution solution;
    solution.moveZeroes(nums);
    return 0;
}