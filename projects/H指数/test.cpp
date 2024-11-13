#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 法1：计数排序 + 逆序搜索 O(n)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int maxCite = *max_element(citations.begin(), citations.end());
        vector<int> nums(maxCite+1, 0);
        // 计数排序，得到引用i次的文章有多少篇的数组
        for (int i = 0; i < citations.size(); i++) {
            nums[citations[i]]++;
        }
        int currNum = 0;
        for (int i = maxCite; i >= 0; i--) {
            // 记录引用大于等于i的文章有多少篇
            currNum += nums[i];
            if (currNum >= i) {
                return i;
            }
        }
        return 0;
    }
};

// 法2：排序 + 逆序搜索 O(nlogn)
class Solution2 {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int h = 0;
        for (int i = citations.size()-1; i >= 0; i--) {
            if (citations[i] > h) {
                h++;
            }else {
                break;
            }
        }
        return h;
    }
};

// 法3：二分查找
class Solution3 {
public:
    int hIndex(vector<int> &citations) {
        int n = citations.size(), left = 0, right = n;

        return binarySearchIfH(citations, left, right);
    }

    int binarySearchIfH(vector<int> &citations, int start, int end) {
        if (start <= end) {
            int mid = (start + end) / 2;
            int cnt = 0;
            for (int i = 0; i < citations.size(); i++) {
                if (citations[i] >= mid) {
                    cnt++;
                }
            }
            if (cnt < mid) {
                // 说明mid需要更小，那么end改为mid-1
                return binarySearchIfH(citations, start, mid - 1);
            } else {
                return binarySearchIfH(citations, mid + 1, end);
            }
        }
        return end;
    }
};




