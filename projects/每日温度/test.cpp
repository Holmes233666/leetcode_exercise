#include<vector>
#include<iostream>
#include<deque>

using namespace std;

// 数组做法
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> nextHighTemps = vector<int> (temperatures.size(), 0);
        for (int i = temperatures.size()-2; i >= 0; i--) {
            int k = i + 1;
            while (temperatures[k] <= temperatures[i] && nextHighTemps[k] != 0) {
                k += nextHighTemps[k];
            }
            if (nextHighTemps[k] == 0 && temperatures[k] <= temperatures[i]) {
                continue;
            }
            nextHighTemps[i] = k - i;
        }
        return nextHighTemps;
    }
};

// 单调栈做法
class Solution2 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> nextHighTemps = vector<int> (temperatures.size(), 0);
        deque<pair<int, int>> dq;   // pair: 数值，idx
        dq.push_back({temperatures[0], 0});
        for (int i = 1; i < temperatures.size(); i++) {
            while (!dq.empty() && temperatures[i] > dq.back().first) {
                nextHighTemps[dq.back().second] = i - dq.back().second;
                dq.pop_back();
            }
            dq.push_back({temperatures[i], i});
        }
        return nextHighTemps;
    }
};


int main() {
    vector<int> nums = {89,62,70,58,47,47,46,76,100,70};
    Solution s;
    vector<int> res = s.dailyTemperatures(nums);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " " ;
    }
    return 0;
}