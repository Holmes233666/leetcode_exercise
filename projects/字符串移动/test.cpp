#include<vector>
#include<iostream>
#include<unordered_map>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<int> ifCircle(vector<int>& nums) {
        // 计算-i为止，是否存在和为0的子数组
        // 输入颠倒
        reverse(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> res(n, 0);
        unordered_map<int, int> umap;
        umap[0] = 1;
        int currSum = 0;
        for (int i = 0; i < n; i++) {
            currSum += nums[i];
            if (umap.find(currSum) != umap.end()) {
                res[n-1-i] = 1;
            }
            umap[currSum]++;
        }
        return res;
    }
};

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        if (s[i] == '<') {
            nums.push_back(1);
        }else {
            nums.push_back(-1);
        }
    }
    Solution solution;
    vector<int> res = solution.ifCircle(nums);
    for (int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }
    return 0;
}
