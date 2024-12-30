#include<vector>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>> f = triangle;
        int n = triangle.size(), minRes = INT_MAX;
        for (int i = 1; i < n; i++) {
            int m = triangle[i].size();
            for (int j = 0; j < m; j++) {
                f[i][j] = min(f[i-1][j], f[i-1][j-1]) + f[i][j];
                if (j == m-1) minRes = min(f[i][j], minRes);
            }
        }
        return minRes;
    }
};
