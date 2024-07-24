#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

// 哈希表+扫描两遍：不考虑O(1)的空间复杂度，只考虑O(n)的时间复杂度
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_map<int, int> umap;
        int minNum = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= 0) continue;
            if (!umap.count(nums[i])) umap[nums[i]]++;
        }
        for (int i = 1; i < INT_MAX; i++) {
            if(!umap.count(i)) return i;
        }
        return 0;
    }
};

int main() {
    vector<int> nums = {1,2,0};
    Solution solution;
    int num = solution.firstMissingPositive(nums);
    cout << num << endl;
    return 0;
}