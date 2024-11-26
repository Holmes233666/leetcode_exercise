#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> umap;   // key: 数值，value：为该数值的最新的索引
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (umap.find(nums[i]) != umap.end()) { // 集合里有这个数
                if (abs(umap[nums[i]] - i) <= k) {
                    return true;
                }
                umap[nums[i]] = i;
            }else { // 集合里没有这个数
                umap[nums[i]] = i;
            }
        }
    }
};