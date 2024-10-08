#include<vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = nums[0], count = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == candidate) count++;
            if (nums[i] != candidate && count >= 1) count--;
            if (count == 0) {
                candidate = nums[i];
                count = 1;
            }
        }
        return candidate;
    }
};