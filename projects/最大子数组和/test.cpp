#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> res(nums.size());
        res[0] = nums[0];
        int maxSum = res[0];
        for (int i = 1; i < nums.size(); i++) {
            if (res[i-1] >= 0) {
                res[i] = nums[i] + res[i-1];
            }else {
                res[i] = nums[i];
            }
            maxSum = max(maxSum, res[i]);
        }
        return maxSum;
    }
};

int main() {
    Solution solution;
    vector<int> vec = {-2,1,-3,4,-1,2,1,-5,4};
    int num = solution.maxSubArray(vec);
    cout << "The Final Res Is: " << num << endl;
    return 0;
}