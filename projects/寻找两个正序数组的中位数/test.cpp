#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 数组长度为偶数，返回中间两数和的平均
        if ((nums1.size() + nums2.size()) % 2 == 0) {
            int k1 = (nums1.size() + nums2.size()) / 2;
            int k2 = k1 + 1;
            return (getKth(nums1, nums2, k1, 0, 0) + getKth(nums1, nums2, k2, 0, 0)) / 2.0;
        }else {
            int k = (nums1.size() + nums2.size()) / 2 + 1;
            return getKth(nums1, nums2, k, 0, 0);
        }
    }

    double getKth(vector<int>& nums1, vector<int>& nums2, int K, int left1, int left2) {
        if (left1 == nums1.size()) return nums2[left2 + K - 1];
        if (left2 == nums2.size()) return nums1[left1 + K - 1];
        if (K == 1) return min(nums1[left1], nums2[left2]);
        // 如果有越界的情况：
        int pivotIdx1 = left1 + K/2 - 1 >= nums1.size() ? nums1.size() - 1 : left1 + K/2 - 1;
        int pivotIdx2 = left2 + K/2 - 1 >= nums2.size() ? nums2.size() - 1 : left2 + K/2 - 1;
        if (nums1[pivotIdx1] <= nums2[pivotIdx2]) {
            int newK = K - ((K/2 - 1) + 1);
            if (left1 + K/2 - 1 >= nums1.size()){
                newK = K - (nums1.size() - 1 - left1 + 1);
            }
            return getKth(nums1, nums2, newK, pivotIdx1+1, left2);
        }else {
            // 如果数组2没有越界：排除nums2前k/2-1个个元素以及nums1[left1 + K/2 - 1]
            int newK = K - ((K/2 - 1) + 1);
            if (left2 + K/2 - 1 >= nums2.size()){
                newK = K - (nums2.size() - 1 - left2 + 1);
            }
            return getKth(nums1, nums2, newK, left1, pivotIdx2+1);
        }
    }
};

// 第二次刷
class Solution2 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if ((n + m) % 2 == 0) {
            return (getKth(nums1, nums2, 0, 0, (m+n)/2)+getKth(nums1, nums2, 0, 0, (m+n)/2-1))/2.0;
        }
        return getKth(nums1, nums2, 0, 0, (m+n)/2);
    }

    int getKth(vector<int>& nums1, vector<int>& nums2, int start1, int start2, int k) {
        int n = nums1.size(), m = nums2.size();
        if (start1 >= n || start2 >= m) {
            return start1 >= n ? nums2[start2 + k] : nums1[start1 + k];
        }
        if (k == 0) return min(nums1[start1], nums2[start2]);
        int cmp_num = (k + 1) / 2 - 1, cmp_idx1 = start1 + cmp_num, cmp_idx2 = start2 + cmp_num;
        if (cmp_idx1 >= n) cmp_idx1 = n-1;
        if (cmp_idx2 >= m) cmp_idx2 = m-1;

        if (nums1[cmp_idx1] <= nums2[cmp_idx2]) {    // 排除nums1 cmp_idx1之前的所有数（包括cmp_idx1）
            return getKth(nums1, nums2, cmp_idx1+1, start2, k-(cmp_idx1-start1+1));
        }
        return getKth(nums1, nums2, start1, cmp_idx2+1, k-(cmp_idx2-start2+1));
    }
};




int main() {
    return 0;
}