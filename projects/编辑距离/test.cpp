#include<string>
#include<vector>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        vector<vector<int>> dp = vector<vector<int>>(n1+1, vector<int>(n2+1, 0));
        // 首先初始化，从word1的前i个字符到word20个字符的值等于word1此时的长度
        for (int i = 1; i <= word1.size(); i++) {
            dp[i][0] = i;
        }
        // 从word2的前若干个字符到word1的前0个字符的值等于word2此时的长度
        for (int j = 1; j <= word2.size(); j++) {
            dp[0][j] = j;
        }
        // 开始填表
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                // 取：A中增加一个字符，在B中增加一个字符，更改A中的一个字符 三者中最小的
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = min(min(dp[i][j-1]+1, dp[i-1][j]+1), dp[i-1][j-1]);
                }else{
                    dp[i][j] = min(min(dp[i][j-1]+1, dp[i-1][j]+1), dp[i-1][j-1]+1);
                }

            }
        }
        return dp[n1][n2];
    }
};