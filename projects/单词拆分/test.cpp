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