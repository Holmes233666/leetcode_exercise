#include<vector>
#include<unordered_map>
#include<iostream>

using namespace std;

// 法1：前缀和+二分查找。都是非负数保证了前缀和一定是递增的，可以使用二分查找。时间复杂度为O(nlogn)
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(), minLen = INT_MAX;
        vector<int> preSum(n+1, 0);
        // 记录前缀和数组
        preSum[0] = 0;
        for (int i = 1; i <= n; i++) {
            preSum[i] = preSum[i-1] + nums[i-1];
        }
        // 对每一个位置，进行二分查找，二分查找的时间复杂度是log(n)，因此整体的时间复杂度是nlogn
        for(int i = 0; i < n; i++) {
            int to_find = preSum[i] + target;
            auto find = lower_bound(preSum.begin(), preSum.end(), to_find);
            if (find != preSum.end()) {   // 能够找到一个下标： preSum[findIdx] - preSum[i] >= target
                minLen = min(minLen, int(find - preSum.begin()) - i);
            }
        }
        return minLen == INT_MAX ? 0 : minLen;
    }
};


// 法2：滑动窗口，时间复杂度O(n)
class Solution2 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(), right = 0, left = 0, currSum = nums[0], minLen = INT_MAX;
        while (right < n) {
            if (currSum == target) {    // 窗口左右边界都向前移动
                minLen = min(minLen, right - left + 1);
                currSum -= nums[left];
                left++;
                right++;
                if (right <= n-1) currSum += nums[right];
            }else if (currSum < target) {   // 那边右边界递增
                right++;
                if (right <= n-1) currSum += nums[right];
            }else {
                minLen = min(minLen, right - left + 1);
                currSum -= nums[left];
                left++;
                if (left > right && left < n) {
                    right++;
                    currSum += nums[right];
                }
            }
        }
        return minLen == INT_MAX ? 0 : minLen;
    }
};

// 滑动窗口：根据题解优化---滑动窗口模板
class Solution3 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(), start = 0, end = 0, currSum = 0, minLen = INT_MAX;
        while (end < n) {
            currSum += nums[end];
            while (currSum >= target) {
                minLen = min(minLen, end - start + 1);
                currSum -= nums[start++];
            }
            end++;
        }
        return minLen == INT_MAX ? 0 : minLen;
    }
};


int main() {
    vector<int> test = {2,3,1,2,4,3};
    int k = 7;
    Solution2 s;
    s.minSubArrayLen(k, test);
    return 0;
}