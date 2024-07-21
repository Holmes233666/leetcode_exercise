#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_map;
        // 将元素放入哈希表，key为元素值，value为元素的下标
        for (int i = 0; i < nums.size(); i++) {
            hash_map[nums[i]] = i;
        }

        // 遍历数组，查找target - nums[i]是否在哈希表中
        for(int i = 0; i <nums.size(); i++) {
            int temp = target - nums[i];
            if (hash_map.count(temp) && hash_map[temp] != i) {
                return {i, hash_map[temp]};
            }
        }
        return {};
    }
};

// 提升版本 只进行一次循环
class improvedSolution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_map;
        for (int i = 0; i < nums.size(); i++) {
            auto it = hash_map.find(target - nums[i]);
            if (it != hash_map.end()) {
                return {it->second, i};
            }
            hash_map[nums[i]] = i;
        }
        return {};
    }
};