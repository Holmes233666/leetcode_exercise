#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


// 法1：计数排序 + 逆序搜索
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

// 法2：计数排序 + 二分查找




