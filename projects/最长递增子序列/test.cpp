#include<vector>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), maxLen = 1;
        vector<int> f(n, 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    f[i] = max(f[i], f[j]+1);
                    maxLen = max(f[i], maxLen);
                }
            }
        }
        return maxLen;
    }
};

// 法2：贪心 + 二分
class Solution2 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), maxLen = 1;
        vector<int> d(n+1, 0);
        d[1] = nums[0];
        for (int i = 1; i < n; i++) {
            if (nums[i] > d[maxLen]) {  // 串可以更长
                d[maxLen+1] = nums[i];
                maxLen++;
            }else { // 新的元素需要尝试在d中找一个位置
                int len = binarySearch(d, 1, maxLen, nums[i]);   // 尝试找nums[i]-1的位置
                d[len] = nums[i];
            }
        }
        return maxLen;
    }

    int binarySearch(vector<int>& d, int start, int end, int target) {   // target应该插入在哪里？
        if (start <= end) {
            int mid = (start + end) / 2;
            if (d[mid] == target) return mid;
            if (d[mid] > target) return binarySearch(d, start, mid-1, target);
            return binarySearch(d, mid+1, end, target);
        }
        return start;   // 返回idx;
    }
};