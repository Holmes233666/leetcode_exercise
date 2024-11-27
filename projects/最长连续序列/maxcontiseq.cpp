#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>

using namespace std;

// 利用桶排序：内存溢出版本
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        auto min_num = min_element(nums.begin(), nums.end());
        // 如果整个数组中的最小数值是负数，那么可以将所有的数值增加
        int move_step = 0;
        if (min_num != nums.end()) {
            move_step = -1 * (*min_num);
        }else {
            return 0;
        }
        // 将每个数都向前移动Move_step
        for (int i = 0; i < nums.size(); i++) {
            nums[i] += move_step;
        }
        
        // 现在所有的数都是非负数，然后再进行列数
        auto max_num = max_element(nums.begin(), nums.end());
        vector<int> bucket(*max_num + 1);
        unordered_map<int, int> umap;
        
        for (int i = 0; i < nums.size(); i++) {
            bucket[nums[i]] = 1;
        }

        // 对bucket进行处理
        for (int i = 1; i < bucket.size(); i++) {
            if (bucket[i] != 0) {
                bucket[i] += bucket[i-1];
            }
        }

        // 找到最大的bucket数组中的数值
        auto it = max_element(bucket.begin(), bucket.end());

        if (it != bucket.end()) {
            return *it;
        }
        
        return 0;

    }
};

class Solution2 {
public:
    int longestConsecutive(vector<int>& nums) {
        int longestStreak = 0;
        // 将所有的数字都放到map里
        unordered_set<int> set;
        for (int i = 0; i<nums.size(); i++) {       
            set.insert(nums[i]);
        }
        // 遍历nums，尝试将每个数作为序列x,x+1,x+2,...,x+y的头
        for (const int num : set) {
            // 如果没有前序的数值，那么就是序列的第一个数
            if (!set.count(num-1)) {
                int currLen = 1;
                int currNum = num;
                while(set.count(currNum + 1)) {
                    currNum += 1;
                    currLen += 1;
                }
                longestStreak = max(longestStreak, currLen);
            }
        }
        return longestStreak;
    }
};



int main() {
    vector<int> nums = {0,1,2,4,8,5,6,7,9,3,55,88,77,99};
    Solution2 solution;
    int len = solution.longestConsecutive(nums);
    cout << len << endl;
    return 0;
}