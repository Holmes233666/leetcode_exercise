#include<vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size()-1;
        while (right > left) {
            if (numbers[right] + numbers[left] == target) {
                return {left, right};
            }
            if (numbers[right] + numbers[left] > target) {
                left--;
            }else {
                right++;
            }
        }
        return {};
    }
};