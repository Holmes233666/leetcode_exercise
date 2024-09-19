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

int main() {
    return 0;
}