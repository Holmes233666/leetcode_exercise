#include<vector>
#include<unordered_map>
#include<iostream>

using namespace std;


class Solution {
public:
    vector<int> ifLetter = vector<int>(26, 0);
    vector<int> res;
    unordered_map<char, int> umap;
    vector<int> nextLetterLoc;
    vector<int> partitionLabels(string s) {
        nextLetterLoc = vector<int>(s.size(), 0);
        for (int i = s.size()-1; i >= 0; i--) {
            if (umap[s[i]] == 0) umap[s[i]] = i;    // 第一次出现
            // 记录umap中最后一次出现的位置
            nextLetterLoc[i] = umap[s[i]];
        }
        int start = 0, end = 0;
        while (start < s.size()) {
            end = getAStr(s, start);
            res.push_back(end - start + 1);
        }
        return res;
    }

    int getAStr(string& s, int start) {
        // 找到start和start字母最后一次出现的位置之间的所有字母的下一个位置
        int nextIdxofStart = nextLetterLoc[start];
        int len = nextIdxofStart - start + 1, end = nextIdxofStart;
        if (nextIdxofStart == start) return len;
        // 记录中间出现的字母的下一个最大位置，初始最大位置为start字母出现的下一个最大位置。
        for (int i = start + 1; i < end; i++) {
            len = max(nextLetterLoc[i] - start + 1, len);
            end = max(end, nextLetterLoc[i]);
        }
        res.push_back(end - start + 1);
        return end;
    }
};