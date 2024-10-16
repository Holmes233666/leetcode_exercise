#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> sorted = nums1;
        int p0=0, p1=0, p=0;
        while (p < m+n) {
            if (m != 0 && n != 0 && nums1[p0] <= nums2[p1]) {
                sorted[p++] = nums1[p0++];
            }else if (m != 0 && n != 0 && nums1[p0] > nums2[p1]){
                sorted[p++] = nums2[p1++];
            }

            if (p0 == m) {  // 扫尾只剩下p1
                while (p1 < n) {
                    sorted[p++] = nums2[p1++];
                }
            }else if (p1 == n) {
                while (p0 < m) {
                    sorted[p++] = nums1[p0++];
                }
            }
        }

        // 拷贝回nums1
        for (int i = 0; i < sorted.size(); i++) {
            nums1[i] = sorted[i];
        }
    }
};