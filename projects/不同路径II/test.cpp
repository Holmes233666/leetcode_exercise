#include<vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (obstacleGrid[i][j] != 0) {  // 不是走不通的路
                    if (j == 0) {
                        obstacleGrid[i][j] = obstacleGrid[i-1][j];
                    }else {
                        obstacleGrid[i][j] = obstacleGrid[i-1][j] + obstacleGrid[i][j-1];
                    }
                }
            }
        }
        return obstacleGrid[n-1][m-1];
    }
};
