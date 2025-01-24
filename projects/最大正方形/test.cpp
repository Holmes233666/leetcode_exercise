#include <vector>

using namespace std;

class Solution {
public:
    int maximalSquare(std::vector<vector<char>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> resMat(n, vector<int>(m, 0));
        int maxSq = 0;
        // 初始化
        for (int j = 0; j < m; j++) {
            resMat[0][j] = matrix[0][j] - '0';
            if (matrix[0][j] == '1') maxSq = 1;
        }
        for (int i = 0; i < n; i++) {
            resMat[i][0] = matrix[i][0] - '0';
            if (matrix[i][0] == '1') maxSq = 1;
        }
        // 开始计算
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] != '0') {
                    resMat[i][j] = pow(min(min(sqrt(resMat[i][j-1]), sqrt(resMat[i-1][j])), sqrt(resMat[i-1][j-1]))+1, 2);
                    maxSq = max(maxSq, resMat[i][j]);
                }
            }
        }
        return maxSq;
    }
};
