#include <vector>
#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 定义四个方向
        vector<vector<int>> directions = {{0,1}, {1,0},{0,-1},{-1,0}};   // 右，下，左，上
        unordered_set<string> uset;
        int count = 0, term = 0, last_i = 0, last_j = 0;
        int totNum = matrix.size() * matrix[0].size();
        vector<int> res;
        while(count < totNum) {
            vector<int> currDire = directions[term % 4];
            while (last_i >= 0 && last_i < matrix.size() && last_j >= 0 && last_j < matrix[0].size() && !uset.count(to_string(last_i) + "," + to_string(last_j))) {
                uset.insert(to_string(last_i) + "," + to_string(last_j));
                count++;
                res.push_back(matrix[last_i][last_j]);
                last_i += currDire[0];
                last_j += currDire[1];
            }
            // 回退一步
            last_i -= currDire[0];
            last_j -= currDire[1];
            // 改变方向
            term++;
            // 更新方向
            last_i += directions[term % 4][0];
            last_j += directions[term % 4][1];
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<int> result = sol.spiralOrder(matrix);
    for (int num : result) {
        cout << num << " ";
    }
    return 0;
}