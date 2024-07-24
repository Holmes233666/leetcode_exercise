#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // 计算前缀积和后缀积
        vector<int> prexPro(nums.size());
        vector<int> suffPro(nums.size());
        //结果数组
        vector<int> answer(nums.size(),1);
        // 预先设置第一个元素和最后一个元素：
        prexPro[0] = 1;
        suffPro[nums.size()-1] = 1;
        // 预准备数组
        for(int i = 1, j = nums.size()-2; i < nums.size(); i++,j--) {
            prexPro[i] = prexPro[i-1] * nums[i-1];
            suffPro[j] = suffPro[j+1] * nums[j+1];
        }
        // 计算answer[i]
        for (int i = 0; i < nums.size(); i++) {
            answer[i] = prexPro[i] * suffPro[i];
        }
        return answer;
    }
};

int main() {
    vector<int> nums = {1,2,3,4,5,6,7};
    Solution solution;
    solution.productExceptSelf(nums);
    return 0;
}