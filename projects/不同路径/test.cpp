#include<vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> f(n, 1);
        for (int j = 1; j < m; j++) {
            for (int i = 1; i < n; i++) {
                f[i] = f[i] + f[i-1];
            }
        }
        return f[n-1];
    }
};