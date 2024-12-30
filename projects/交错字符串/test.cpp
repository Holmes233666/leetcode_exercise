#include<vector>

using namespace std;

// 法1：错误解法，两个串都有某个字母，用哪个串呢？
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s3 == "") return true;
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        for (int i = 0, j = 0, k = 0; i < n3; i++) {
            if (j < n1 && s3[i] == s1[j]) {
                j++;
            }else if (k < n2 && s3[i] == s2[k]) {
                k++;
            }else {
                return false;
            }
        }
        return true;
    }
};

// 法2：从二维dp的角度考虑
class Solution2 {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if (n1 + n2 != n3) return false;
        if (n3 == 0) return true;
        vector<vector<bool>> f(n1+1, vector<bool>(n2+1, true));
        // 初始化矩阵的第一行
        for (int i = 0, j = 1; j <= n2; j++) {
            f[i][j] = f[i][j-1] && (s2[j-1] == s3[i+j-1]);
        }
        // 进行后续计算
        for (int i = 1; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {
                if (j == 0) {
                    f[i][j] = f[i-1][j] && (s1[i-1] == s3[i+j-1]);
                }else {
                    f[i][j] = (f[i-1][j] && (s1[i-1] == s3[i+j-1])) || (f[i][j-1] && (s2[j-1] == s3[i+j-1]));
                }
            }
        }
        return f[n1][n2];
    }
};
