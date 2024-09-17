#include<vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return getInsert(nums, target, 0, nums.size()-1);
    }

    int getInsert(vector<int>& nums, int target, int start, int end) {
        if (start == end) {
            if (nums[start] == target) return start;
            return start + 1;
        }
        int mid = (start + end) / 2;
        if (nums[mid] >= target) {
            return getInsert(nums, target, start, mid);
        }

        return getInsert(nums, target, mid, end);

    }

};