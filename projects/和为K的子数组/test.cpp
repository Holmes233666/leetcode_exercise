#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<unordered_map>

using namespace std;

// 暴力解法：超出时间限制
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            int tempSum = 0;
            for (int j = i; j < nums.size(); j++) {
                tempSum += nums[j];
                if (tempSum == k) {
                    res++;
                }
            }
        }
        return res;
    }
};

// 前缀和
class Solution2 {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0;
        // 遍历一遍数组，使用sums[i]表示以i为结尾的从序号0开始的子数组的和
        vector<int> sums(nums.size(), 0);
        sums[0] = nums[0];
        if (sums[0] == k) res++;
        for (int i = 1; i < nums.size(); i++) {
            sums[i] = sums[i-1] + nums[i];
            if (sums[i] == k) res++;
        }
        // j - k段子数组的和为 sums[k] - sums[j] + nums[j]
        // 枚举所有的j，k可以得到所有子数组的和是否满足条件
        for (int i = nums.size()-1; i >= 1; i--) {
            for (int j = i; j >= 1; j--) {
                // 计算j-i间隔的和
                if ( sums[i]-sums[j] + nums[j] == k) res++;
            }
        }
        return res;
    }
};

// 力扣解法：前缀和 + 哈希表，错误版本：对于k=0的情况，会记录下为空的子数组
class Solution3 {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0;
        // 遍历一遍数组，使用sums[i]表示以i为结尾的从序号0开始的子数组的和
        vector<int> sums(nums.size(), 0);
        unordered_map<int, int> umap;
        umap[0] = 1;
        umap[nums[0]] = 1;
        sums[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            sums[i] = sums[i-1] + nums[i];
            // 记录频次
            umap[sums[i]] += 1;
        }

        // j - i段子数组的和为 sums[i] - sums[j] + nums[j] = sums[i] - sums[j-1]
        for (int i = 0; i < nums.size(); i++) {
            // 等于 k 的段满足：sums[j-1] = sums[i] - k
            if (umap.find(sums[i] - k) != umap.end()) {
                res += umap[sums[i]-k];
            }
        }
        return res;
    }
};

// 前缀和+哈希表
class Solution4 {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0;
        int tempSum = 0;
        unordered_map<int, int> umap;
        umap[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            tempSum += nums[i];
            // 试图找到一个子数组，tempSum减去这个子数组就等于k
            if (umap.find(tempSum - k) != umap.end()) {
                res += umap[tempSum - k];
            }
            umap[tempSum]++;
        }
        return res;
    }
};


int main() {
    vector<int> vec = {1,1,1};
    Solution3 solution;
    int res = solution.subarraySum(vec, 2);
    cout << "result is: " << res << endl;
    return 0;
}
