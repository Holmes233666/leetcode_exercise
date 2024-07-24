#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 朴素想法
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[0] < b[0];
        });
        vector<vector<int>> res;
        for (int i = 0; i < intervals.size();) {
            int end = intervals[i][1];
            int k = i + 1;
            while(k < intervals.size() && end >= intervals[k][0]) {
                if (end < intervals[k][1]) {
                    end = intervals[k][1];
                }
                k++;
            }
            res.push_back({intervals[i][0], end});
            i = k;
        }
        return res;
    }
};

int main() {
    vector<vector<int>> test = {{5,5},{1,2},{2,4},{2,3},{4,4},{5,5},{2,3},{5,6},{0,0},{5,6}};
    Solution solution;
    vector<vector<int>> test2 = solution.merge(test);
    for (int i = 0; i < test2.size(); i++) {
        cout << test2[i][0] << " " << test[i][1] << endl;
    }
    return 0;
}

