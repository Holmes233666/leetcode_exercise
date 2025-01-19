#include<vector>

using namespace std;

// 法1：直观做法，扫描一遍
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size(), resIdx = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i-1] && (i+1 == n || nums[i] > nums[i+1])) {
                return i;
            }
        }
        return resIdx;
    }
};

// 法2： 二分查找
class Solution2 {
public:
    int findPeakElement(vector<int>& nums) {
        return binarySearch(nums, 0, nums.size()-1);
    }

    int binarySearch(vector<int>& nums, int start, int end) {
        if (start == end) {
            if (start == 0 && (start + 1 == nums.size() || nums[start] > nums[start+1])) return start;
            if (start == nums.size()-1 && nums[start] > nums[start-1]) return start;
        }
        if (start < end) {
            int mid = (start + end) / 2;
            if (mid > 0 && nums[mid] > nums[mid+1] && nums[mid] > nums[mid-1]) return mid;
            if (mid == 0 && nums[mid] > nums[mid+1]) return mid;
            if (mid == 0 && nums.size() == 2 && nums[mid+1] > nums[mid]) return mid+1;
            if (mid > 0 && nums[mid] > nums[mid-1] && nums[mid] < nums[mid+1]) {    // 递增
                int idx = binarySearch(nums, mid+1, end);
                if (idx != -1) return idx;
                idx = binarySearch(nums, start, mid);
                return idx;
            }
            if (mid > 0 && nums[mid] < nums[mid-1] && nums[mid] > nums[mid+1]) {    // 递减
                int idx = binarySearch(nums, start, mid);
                if (idx != -1) return idx;
                idx = binarySearch(nums, mid+1, end);
                return idx;
            }
            if (mid > 0 && nums[mid] < nums[mid-1] && nums[mid] < nums[mid+1]) {
                int idx = binarySearch(nums, start, mid);
                if (idx != -1) return idx;
                idx = binarySearch(nums, mid+1, end);
                return idx;
            }
        }
        return -1; // 没找到
    }
};

// 法3： 二分的简化写法
class Solution3 {
public:
    int findPeakElement(vector<int>& nums) {
        return binarySearch(nums, 0, nums.size()-1);
    }

    int binarySearch(vector<int>& nums, int start, int end) {
        if (start == end) return start;
        if (start < end) {
            int mid = (start + end) / 2;
            if (nums[mid] < nums[mid+1]) return binarySearch(nums, mid+1, end);
            return binarySearch(nums, start, mid);
        }
        return -1;
    }
};