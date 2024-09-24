#include<vector>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return randomSelect(nums, 0, nums.size()-1, nums.size() - k + 1);
    }

    int randomSelect(vector<int>& nums, int start, int end, int k) {
        if (start == end) return nums[start];
        int pIdx = Partition(nums, start, end);
        int foundK = pIdx - start + 1;
        if (foundK == k) return nums[pIdx];
        if (foundK < k) return randomSelect(nums, pIdx+1, end, k-foundK);
        return randomSelect(nums, start, pIdx-1, k);
    }

    int Partition(vector<int>& nums, int start, int end) {
        int pivot = nums[end];
        int i = start - 1;
        for (int j = start; j < end; j++) {
            if (nums[j] < pivot) {
                i = i + 1;
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
        int temp = nums[i+1];
        nums[i+1] = pivot;
        nums[end] = temp;
        return i + 1;   // i+1个位置之前是数组中最小的i个数
    }
};

class Solution2 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return randomSelect(nums, 0, nums.size()-1, nums.size() - k + 1);
    }

    int randomSelect(vector<int>& nums, int start, int end, int k) {
        if (start == end) return nums[start];
        int pIdx = Partition(nums, start, end);
        int foundK = pIdx - start + 1;
        if (foundK == k) return nums[pIdx];
        if (foundK < k) return randomSelect(nums, pIdx+1, end, k-foundK);
        return randomSelect(nums, start, pIdx-1, k);
    }

    int Partition(vector<int>& nums, int start, int end) {
        int pivot = nums[end];
        int i = start - 1;
        for (int j = start; j < end; j++) {
            if (nums[j] < pivot) {
                i = i + 1;
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
        int temp = nums[i+1];
        nums[i+1] = pivot;
        nums[end] = temp;
        return i + 1;   // i+1个位置之前是数组中最小的i个数
    }
};

class Solution3 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return randomSelect(nums, 0, nums.size()-1, nums.size() - k);
    }

    int randomSelect(vector<int>& nums, int start, int end, int k) {
        if (start == end) return nums[start];
        int pivot = nums[start], l = start - 1, r = end + 1;
        while (l < r) {
            do l++; while(nums[l] < pivot);
            do r--; while(nums[r] > pivot);
            if (l < r) swap(nums[l], nums[r]);
        }
        if (k <= r) return randomSelect(nums, start, r, k);
        return randomSelect(nums, r+1, end, k);
    }
};


int main() {
    vector<int> nums = {3,2,1,5,6,4};
    Solution s;
    s.findKthLargest(nums, 2);
    return 0;
}
