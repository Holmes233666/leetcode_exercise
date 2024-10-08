#include<vector>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        vector<vector<bool>> f = vector<vector<bool>>(s.size(), vector<bool>(s.size(), true));
        int maxLen = 1, maxStart = 0, maxEnd = 0;
        for (int i = s.size()-2; i >= 0; i--) {
            for (int j = i+1; j < s.size(); j++) {
                f[i][j] = f[i+1][j-1] && (s[i] == s[j]);
                if (f[i][j] && j-i+1 > maxLen) {
                    maxLen = j-i+1;
                    maxStart = i;
                }
            }
        }
        return s.substr(maxStart, maxLen);
    }
};

class Solution2 {
public:
    string longestPalindrome(string s) {
        vector<vector<bool>> f = vector<vector<bool>>(s.size(), vector<bool>(s.size(), true));
        int maxLen = 1, maxStart = 0;
        for (int i = s.size()-2; i >= 0; i--) {
            for (int j = s.size()-3; j > i; j--) {
                f[i][j] = f[i+1][j-1] && (s[i] == s[j]);
                if (f[i][j] && j-i+1 > maxLen) {
                    maxLen = j-i+1;
                    maxStart = i;
                }
            }
        }
        return s.substr(maxStart, maxLen);
    }
};
