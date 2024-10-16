#include<vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // 双指针：其中一个指针后面都是不等于val的数，一个指针负责前进，进行交换
        int right = -1, left = 0;
        while (left < nums.size()) {
            if (nums[left] != val) {
                right++;
                swap(nums[left], nums[right]);
            }
            left++;
        }
    }
};