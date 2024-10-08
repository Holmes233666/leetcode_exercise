#include<vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        vector<int> f = grid[0];
        for (int i = 1; i < grid[0].size(); i++) {
            f[i] = grid[0][i] + f[i-1];
        }
        for (int i = 1; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (j == 0) {
                    f[j] = grid[i][j] + f[j];
                }else {
                    f[j] = min(f[j], f[j-1]) + grid[i][j];
                }
            }
        }
        return f[grid[0].size()-1];
    }
};
