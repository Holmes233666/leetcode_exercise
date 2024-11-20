#include<vector>
#include<iostream>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size();
        vector<string> res;
        for (int i = 0; i < n; ) {
            string currStr;
            int currLen = 0;
            int j = i;
            currLen += words[j++].size();
            while (j < n && currLen + 1 + words[j].size() <= maxWidth) { // 还能放一个单词
                currLen += words[j++].size() + 1; // 单词长度+末尾
            }
            if (j-1 == i) {    // 这个串只有第一个单词，末尾需要补齐所有的空格
                currStr = words[i];
                while (currLen < maxWidth) {    // 补齐剩余的空格
                    currStr.push_back(' ');
                    currLen++;
                }
                res.push_back(currStr);
                i++;
            }else {     // 只能放 j - i + 1个单词，考虑空格的问题
                if (j != n) {
                    int appendBrackets = maxWidth - currLen;    // 计算currLen比maxWidth差几个空格？减掉最后一个单词的空格
                    int gapNum = j - i - 1;     // j - i个地方需要插入空格
                    int bracketEachGap = appendBrackets / gapNum + 1;   // 还有原本需要间隔的一个空格
                    int suplus = appendBrackets - (bracketEachGap-1) * gapNum;
                    while(i < j) {
                        currStr += words[i];
                        i++;
                        // 添上空格
                        if (i != j) {   // 如果不是最后一个单词，那么需要添加空格
                            int bn = bracketEachGap;
                            if (suplus) {   // 如果是余数
                                bn += 1;
                                suplus--;
                            }
                            while (bn > 0) {
                                currStr += " ";
                                bn--;
                            }
                        }
                    }
                }else { // 所有单词都用一个空格间隔即可
                    while(i < j) {
                        currStr += words[i];
                        if (currStr.size() < maxWidth) currStr += " ";
                        i++;
                    }
                    while (currStr.size() < maxWidth) {
                        currStr += " ";
                    }
                }
                res.push_back(currStr);
            }
        }
        return res;
    }
};
