#include<vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zeroCount = 0, oneCount = 0, twoCount = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                zeroCount++;
            }else if (nums[i] == 1) {
                oneCount++;
            }else {
                twoCount++;
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (zeroCount != 0) {
                nums[i] = 0;
                zeroCount--;
            }else if (oneCount != 0) {
                nums[i] = 1;
                oneCount--;
            }else {
                nums[i] = 2;
                twoCount--;
            }
        }
    }
};

// 参考快速排序的pivot做法一i一j，一个往前扫，一个记录当前的最后一个0的位置
class Solution2 {
public:
    void sortColors(vector<int>& nums) {
        // 先排好所有的0
        int last_zero = -1;
        for (int left = 0; left < nums.size(); left++) {
            if (nums[left] == 0) {
                last_zero++;
                swap(nums[last_zero], nums[left]);
            }
        }
        int last_one = last_zero;
        for (int left = last_one-1; left < nums.size(); left++) {
            if (nums[left] == 1) {
                last_one++;
                swap(nums[left], nums[last_one]);
            }
        }
    }
};
