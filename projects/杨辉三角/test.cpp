#include<vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        // 先创造相应的矩阵的形状
        vector<vector<int>> res;
        for (int i = 1; i <= numRows; i++) {
            vector<int> newVec = vector<int>(i,1);
            res.push_back(newVec);
        }
        for (int i = 3; i <= numRows; i++) {
            // 从第3行开始
            for (int j = 1; j < res[i-1].size()-1; j++) {
                res[i-1][j] = res[i-2][j-1] + res[i-2][j];
            }
        }
        return res;
    }
};