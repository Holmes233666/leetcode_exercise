#include<vector>

using namespace std;

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> f(n+1, vector<int>(m+1));
        for (int j = 1; j <= m; j++) {
            f[0][j] = f[0][j-1] + int(s2[j-1]);
        }
        for (int i = 1; i <= n; i++) {
            f[i][0] = f[i-1][0] + int(s1[i-1]);
        }
        // 填表
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i-1] == s2[j-1]) f[i][j] = f[i-1][j-1];
                if (s1[i-1] != s2[j-1]) f[i][j] = min(f[i][j-1] + int(s2[j-1]), f[i-1][j] + int(s1[i-1]));
            }
        }
        return f[n][m];
    }
};
