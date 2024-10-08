#include<vector>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> f = vector<vector<int>>(text1.size(), vector<int>(text2.size(), 0));
        int maxLen = 0;
        // 初始化第一行和第一列的结果
        for (int i = 0; i < text1.size(); i++) {
            if (text2[0] == text1[i]) f[i][0] = 1;
        }
        for (int j = 0; j < text2.size(); j++) {
            if (text1[0] == text2[j]) f[0][j] = 1;
        }

        for (int i = 1; i < text1.size(); i++) {
            for (int j = 1; j < text2.size(); j++) {
                if (text1[i] == text2[j]) {
                    f[i][j] = f[i-1][j-1] + 1;
                    maxLen = max(maxLen, f[i][j]);
                }
            }
        }
        return maxLen;
    }
};