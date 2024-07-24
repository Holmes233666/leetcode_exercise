#include<iostream>
#include<vector>

using namespace std;

// 我的做法
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        vector<int> res(nums.size(), 0);
        for (int i = nums.size()-1, rote_num = 0; rote_num < k; i--) {
            res[k-rote_num-1] = nums[i];
            rote_num++;
        }
        for (int i = 0; i <= nums.size() - k - 1; i++) {
            res[i+k] = nums[i];
        }
        nums = res;
    }
};

// 力扣题解，直接将所有的元素都放到： (i + k) mod n的位置
class Solution2 {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> res(nums.size(), 0);
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            res[(i + k) % n] = nums[i];
        }
        nums = res;
    }
};

// 力扣题解做法：翻转数组+swap
class Solution3 {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k % n);
        reverse(nums.begin() + k % n, nums.end());
    }
};

int main() {
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 3;
    Solution solution;
    solution.rotate(nums, k);
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    return 0;
}