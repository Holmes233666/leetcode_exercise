#include <iostream>
#include<vector>
#include<unordered_map>

using namespace std;

// 法1：暴力解法，以字母为单位移动
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = words.size(), m = words[0].size();
        int slen = s.size();
        int win_size = m * n;
        vector<int> res;
        unordered_map<string, int> umap, currMap, newMap;
        for (int i = 0; i < n; i++) {
            umap[words[i]]++;
        }
        int totWords = umap.size();
        // 外层枚举大小为n*m的窗口
        for (int left = 0, right = 0; right < slen; right++) {
            int wordNum = 0;
            string nextStr;
            if (right - left + 1 == win_size) {
                // 更新map中的元素
                currMap = newMap;
                for (int i = left; wordNum <= n; i += m) {
                    string currStr = s.substr(i, m);
                    if (umap.find(currStr) == umap.end()) break;    // 没有这个单词
                    currMap[currStr]++; // 有这个单词
                    if (umap[currStr] == currMap[currStr]) {
                        totWords--;
                    }
                    if (umap[currStr] < currMap[currStr]) break;    // 目前的单词超过数量了
                    wordNum++;
                }
                if (wordNum == n && totWords == 0) {   // 正常退出
                    res.push_back(left);
                }
                left++; // 左边界收缩
            }
            totWords = umap.size();
        }
        return res;
    }
};

// 法2：外层移动字母，内层滑动窗口
class Solution2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = words.size(), m = words[0].size();
        int slen = s.size();
        int win_size = m * n;
        if (slen < win_size) return {};
        vector<int> res;
        unordered_map<string, int> umap;
        for (int i = 0; i < n; i++) {
            umap[words[i]]++;
        }
        for (int i = 0; i < m && i + win_size <= slen; i++) {
            unordered_map<string, int> currMap;
            // 记录新窗口内的单词
            int wordNum = umap.size();
            for (int start = i, end = i; end < start + win_size; end += m) {
                string currStr = s.substr(end, m);
                currMap[currStr]++;
                if (umap.find(currStr) != umap.end() && umap[currStr] == currMap[currStr]) {
                    wordNum--;
                }
            }
            if (wordNum == 0) res.push_back(i);
            // 滑动窗口
            for (int right = i, left = i + win_size - 1; left + m < slen; right += m, left += m) {
                string moveStr = s.substr(right, m);
                string inStr = s.substr(left + 1, m);
                currMap[moveStr]--;
                currMap[inStr]++;
                if (umap.find(inStr) != umap.end() && currMap[inStr] == umap[inStr] && inStr != moveStr) wordNum--;
                if (umap.find(moveStr) != umap.end() && currMap[moveStr] == umap[moveStr]-1 && inStr != moveStr) wordNum++;
                if (wordNum == 0) res.push_back(right + m);
            }
            // 上一段的逻辑简化：
            // for (int right = i, left = right + win_size - 1; left + m < slen; right += m, left += m) {
            //     string moveStr = s.substr(right, m);
            //     string inStr = s.substr(left + 1, m);
            //     currMap[moveStr]--;
            //     if (umap.find(moveStr) != umap.end() && currMap[moveStr] == umap[moveStr]-1) wordNum++;
            //     currMap[inStr]++;
            //     if (umap.find(inStr) != umap.end() && currMap[inStr] == umap[inStr]) wordNum--;
            //     if (wordNum == 0) res.push_back(right + m);
            // }
        }
        return res;
    }
};
