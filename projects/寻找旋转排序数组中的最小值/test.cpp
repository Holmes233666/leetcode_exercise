#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int pIdx = -1;
        searchPivot(nums, 0, nums.size()-1, pIdx);
        return pIdx == nums.size()-1 ? nums[0] : nums[pIdx + 1];
    }

    void searchPivot(vector<int>& nums, int start, int end, int& pIdx) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] < nums[0]) {
                searchPivot(nums, start, mid - 1, pIdx);
            }else {
                pIdx = mid;
                searchPivot(nums, mid + 1, end, pIdx);
            }
        }
    }
};

class Solution2 {
public:
    int findMin(vector<int>& nums) {
        int pIdx = -1;
        searchPivot(nums, 1, nums.size()-1, pIdx);
        return pIdx == -1 ? nums[0] : nums[pIdx];
    }

    void searchPivot(vector<int>& nums, int start, int end, int& pIdx) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] < nums[0]) {
                pIdx = mid;
                searchPivot(nums, start, mid - 1, pIdx);
            }else {
                searchPivot(nums, mid + 1, end, pIdx);
            }
        }
    }
};



int main() {
    return 0;
}