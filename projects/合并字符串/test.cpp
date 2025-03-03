//
// Created by 孙蕴琦 on 2025/2/25.
//
#include<vector>

using namespace std;

class Solution {
public:
    vector<string> mergeStr(vector<string>& strs, int maxLen) {
        int n = strs.size();
        vector<string> res;
        for (int i = 0; i < n; ) {
            string currStr = strs[i];
            int j = i;
            string tempStr = "";
            while (j < n && (tempStr.size() == 0 || tempStr.size() + strs[j].size() + 1 <= maxLen)) {
                if (tempStr != "") tempStr += "|";
                tempStr += strs[j];
                j++;
            }
            i = j;
            res.push_back(tempStr);
        }
        return res;
    }
};

vector<string> mergeStr(vector<string>& strs, int maxLen) {
    vector<string> res;
    int i = 0, n = strs.size();
    while (i < n) {
        // 开始组装新的一行
        string line = strs[i];
        int lineLen = line.size();  // 当前行的长度
        i++;

        // 在这之后，尝试往本行追加后续字符串
        while (i < n) {
            // 如果再加一个 "|" + strs[i] 会不会超过 maxLen？
            int sepLen = (line.empty() ? 0 : 1); // 如果行不为空，需要1个分隔符
            if (lineLen + sepLen + (int)strs[i].size() <= maxLen) {
                // 可以拼接
                if (!line.empty()) {
                    line += "|";
                    lineLen += 1;  // 分隔符长度
                }
                line += strs[i];
                lineLen += strs[i].size();
                i++;
            } else {
                // 超过了，就该换行
                break;
            }
        }
        res.push_back(line);
    }
    return res;
}

