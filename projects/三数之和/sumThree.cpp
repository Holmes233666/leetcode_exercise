#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>
#include<algorithm>

using namespace std;

// 超时解法
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> finalRes;
        for (int i=0; i < nums.size(); i++) {
            // 对于nums[i]的剩余值，找满足两数之和的结果
            int res = -nums[i];
            // 找两数之和为res;
            set<int> hash_map;
            for (int j = i + 1; j < nums.size(); j++) {
                vector<int> aRes;
                auto it = hash_map.find(res-nums[j]);
                if (it != hash_map.end()) {
                    aRes = {nums[i], nums[j], *it};
                    // 对aRes排序
                    sort(aRes.begin(), aRes.end());
                    finalRes.insert(aRes);
                    continue;
                }else{
                    hash_map.insert(nums[j]);
                }
            }
        }
        // 将set改为vector
        vector<vector<int>> ResVec;
        for (const auto& it : finalRes) {
            ResVec.push_back(it);
        }
        return ResVec;
    }
};

// 双指针
class Solution2 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 初始化为空
        vector<vector<int>> res_vec = {};
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++) {
            if (i >= 1 && nums[i] == nums[i-1]) {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            int target = -nums[i];
            while (right > left) {
                if (nums[right] + nums[left] > target) {
                    right--;
                }else if(nums[right] + nums[left] < target){
                    left++;
                }else{  // 刚好满足两数之和
                    // res_set.insert({nums[i], nums[right], nums[left]});
                    res_vec.push_back({nums[i], nums[right], nums[left]});
                    // 右移左指针
                    left++;
                    // 避免枚举和上次一样的数值
                    while (left < right && nums[left] == nums[left-1]) {
                        left++;
                    }
                }
            }
        }
        return res_vec;
    }
};

int main() {
    Solution2 solution;
    vector<int> vec3 = {0,0,0,0};
    solution.threeSum(vec3);
    return 0;
}