#include<vector>

using namespace std;

// 法1：纵向比较
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size(), minLen = INT_MAX;
        // 所有的字符串，找到长度最短的串
        for (int i = 0; i < n; i++) {
            int currLen = strs[i].size();
            minLen = min(minLen, currLen);
        }
        int len = 0;
        string res = "";
        for (int i = 0; i < minLen; i++) {
            char currChar = strs[0][i];
            for (int j = 1; j < n; j++) {
                if (strs[j][i] == currChar) {
                    res.push_back(currChar);
                }else {
                    return res;
                }
            }
        }
        return res;
    }
};

// 法2：排序
