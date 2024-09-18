#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        // 首先二分寻找pivot
        int start = 1, end = nums.size()-1, pivotIdx = -1;
        searchPivot(nums, start, end, pivotIdx);
        // 然后对pivot两边进行两次二分查找
        int idxLeft = binarySearch(target, 0, pivotIdx, nums);
        if (idxLeft == -1) {
            int idxRight = binarySearch(target, pivotIdx + 1, end, nums);
            return idxRight == -1 ? -1 : idxRight;
        }
        return idxLeft;
    }

    // 搜索比nums[0]小的最小的数
    void searchPivot(vector<int>& nums, int start, int end, int& minIdx) {
        if (start <= end) {
            int mid = (start + end) / 2;
            // 没有等于的情况，每个数都是不同的
            if (nums[0] > nums[mid]) {
                minIdx = mid;   // mid比nums[0]小的时候，记录min的下标
                searchPivot(nums, start, mid - 1, minIdx);
            }
            searchPivot(nums, mid + 1, end, minIdx);
        }
    }

    int binarySearch(int target, int start, int end, vector<int>& nums) {
        if (start > end) return -1;
        int mid = (start + end) / 2;    // 不越界的写法：end + (start - end) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target) return binarySearch(target, start, mid - 1, nums);
        return binarySearch(target, mid + 1, end, nums);
    }
};

int main() {
    return 0;
}