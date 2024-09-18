#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size() == 0) return {-1,-1};
        int lb = getLowerBound(target, 0, nums.size()-1, nums);
        if (lb == -1) return {-1,-1};
        int ub = getUpperBound(target, 0, nums.size()-1, nums);
        return {lb,ub};
    }

    int getLowerBound(int target, int start, int end, vector<int>& nums) {
        if (start > end) {
            return -1;
        }
        int mid = (start + end) / 2;
        if (nums[mid] < target) return getLowerBound(target, mid + 1, end, nums);
        int res =  getLowerBound(target, start, mid-1, nums);
        if (res == -1) {
            // 如果没找到，那么看看mid
            if (nums[mid] == target) return mid;
            return -1;
        }
        return res;
    }

    int getUpperBound(int target, int start, int end, vector<int>& nums) {
        if (start > end) {
            return -1;
        }
        int mid = (start + end) / 2;

        if (nums[mid] > target) {
            return getUpperBound(target, start, mid-1, nums);  // 递归左半部分
        }
        int res =  getUpperBound(target, mid+1, end, nums);
        if (res == -1) {
            // 如果没找到，那么看看mid
            if (nums[mid] == target) return mid;
            return -1;
        }
        return res;
    }
};

int main() {
    return 0;
}