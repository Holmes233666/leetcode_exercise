#include<vector>
#include<string>
#include<unordered_map>
#include<queue>

using namespace std;

// 方法1：单向广度优先搜索
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n1 = wordList.size();
        unordered_map<string, int> umap;    // 映射string到对应的数组下标
        for (int i = 0; i < n1; i++) {
            umap[wordList[i]] = i;
        }
        // 特殊情况判断：
        if (umap.find(endWord) == umap.end()) return 0;
        // 额外处理beginWord
        int n2 = n1;
        if (umap.find(beginWord) == umap.end()) {
            umap[beginWord] = n1;
            wordList.push_back(beginWord);
            n2 = n1 + 1;
        }
        // 对wordList中的所有单词进行其相邻单词数组的计算
        vector<vector<string>> dictornary(n2, vector<string>());
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                if (i == j || wordList[i].size() != wordList[j].size()) continue;
                int len = wordList[i].size(), differNum = 0;
                for (int k = 0; k < len; k++) {
                    if (wordList[i][k] != wordList[j][k]) {
                        differNum++;
                        if (differNum == 2) break;
                    }
                }
                if (differNum == 1) dictornary[umap[wordList[i]]].push_back(wordList[j]);
            }
        }
        // 根据dictionary的结果，进行广度优先搜索
        queue<string> q;
        q.push(beginWord);
        vector<int> visited(n2, 0);
        visited[umap[beginWord]] = 1;
        int currchoice = 1, step = 1;
        while (!q.empty()) {
            int nextChoice = 0;
            for (int i = 0; i < currchoice; i++) {
                string currStr = q.front();
                q.pop();
                int idx = umap[currStr];
                for (int j = 0; j < dictornary[idx].size(); j++) {
                    string cmpStr = dictornary[idx][j];
                    if (cmpStr == endWord) {
                        if (n2 == n1 + 1) return step + 1;
                        return step;
                    }
                    if (visited[umap[cmpStr]] == 0) {
                        visited[umap[cmpStr]] = 1;
                        q.push(cmpStr);
                        nextChoice++;
                    }
                }
            }
            step++;
            currchoice = nextChoice;
        }
        return 0;
    }
};
