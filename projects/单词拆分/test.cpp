#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> f = vector<bool>(s.size(), false);
        for (int i = 0; i < s.size(); i++) {
            f[i] = false;
            for (int j = 0; j < wordDict.size(); j++) {
                int len = wordDict[j].size();
                if (i + 1 >= len && s.substr((i+1-len, len)) == wordDict[j]) {
                    f[i] = f[i-len] or f[i];
                }
            }
        }
        return f[s.size()-1];
    }
};

class Solution2 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> f = vector<bool>(s.size(), false);
        for (int i = 0; i < s.size(); i++) {
            f[i] = false;   // 初始化
            for (int j = 0; j < wordDict.size(); j++) {
                int len = wordDict[j].size();
                if (i + 1 >= len && s.substr(i+1-len, len) == wordDict[j]) {
                    if (i - len == -1) f[i] = true;
                    f[i] = (f[i] || f[i-len] );
                    if (f[i]) break;
                }
            }
        }
        return f[s.size()-1];
    }
};

// 第二次刷
class Solution3 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size(), m = wordDict.size();
        vector<bool> f(n+1, false);
        f[0] = true;    // s的前0个字母一定能从wordDict中构成，只要不取就行了
        for (int i = 0; i < n; i++) {   // 遍历s的0-n-1下标的字母，判断哪些能够构成
            for (int j = 0; j < m; j++) {
                int len = wordDict[j].size();
                if (i - len + 1 >= 0 && f[i - len + 1] == true && s.substr(i+1-len, len) == wordDict[j]) {
                    f[i+1] = true;
                    break;
                }
            }
        }
        return f[n];
    }
};