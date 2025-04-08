#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

int main() {
    vector<int> nums;
    string str;
    getline(cin, str);
    stringstream ss(str);
    int temp;
    while (ss >> temp) {
        nums.push_back(temp);
    }
    int n = nums.size();
    vector<int> numsStack;
    numsStack.push_back(nums[0]);
    for (int i = 1; i < n; i++) {
        for (int j = numsStack.size()-1, sum = 0; j >= 0; j--) {
            sum += numsStack[j];
            if (sum == nums[i]) {   // 如果到当前的数满足了 前几块的和 == 当前块
                for (int k = numsStack.size()-1; k >= j; k--) {
                    numsStack.pop_back();
                }
                numsStack.push_back(nums[i] * 2);
                break;
            }
            if (sum > nums[i]) {
                numsStack.push_back(nums[i]);
                break;
            }
            if (sum < nums[i] && j == 0) {
                numsStack.push_back(nums[i]);
            }
        }
        // cout << "------------------" << endl;
    }
    // 将结果逆序输出
    for (int i = numsStack.size()-1; i >= 0; i--) {
        cout << numsStack[i] << " ";
    }

}