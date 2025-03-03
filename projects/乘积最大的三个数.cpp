#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    int getMax(vector<int>& nums) {
        int n = nums.size();
        // 两种可能：一是最大的三个正数，二是最小的两个负数 * 最大的正数
        sort(nums.begin(), nums.end());
        return nums[0] < 0 ? max(nums[0]*nums[1]*nums[n-1], nums[n-1]*nums[n-2]*nums[n-3]) : nums[n-1]*nums[n-2]*nums[n-3];
    }
};

// 输入不知道有多少个数，需要整行读取
int main() {
    string input;
    vector<int> nums;
    getline(cin, input);    // 注意读取一整行的写法
    stringstream ss(input);
    string temp;
    // 第一种写法
    // while(getline(ss, temp, ' ')) {
    //     nums.push_back(stoi(temp));
    // }
    int num;
    while (ss >> num) {
        nums.push_back(num);
    }
    Solution s;
    cout << s.getMax(nums) << endl;
}

