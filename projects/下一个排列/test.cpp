#include<vector>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // 如果正好是逆序，那么没法构成更大的排列，直接返回最小的排列
        int flag = -1;
        for (int i = nums.size()-1; i >= 1; i--) {
            if (nums[i] > nums[i-1]) {
                flag = i;
                break;
            }
        }
        // 说明该排列是最大的排列，那么直接reverse
        if (flag == -1) {
            reverse(nums.begin(), nums.end());
        }else {// 找到了左边的较小数
            // 然后找右边的较大数，并保证较大数尽可能靠右
            int idx = -1;
            for (int i = nums.size()-1; i >= flag; i--) {
                if (nums[i] > nums[flag]) {
                    idx = i;
                    break;
                }
            }
            // 交换两个数的位置
            swap(nums[idx], nums[flag]);
            // 最后将较大数后面的数改为升序，即现在的flag后面的数改为升序
            reverse(nums.begin()+flag+1, nums.end());
        }
    }
};
