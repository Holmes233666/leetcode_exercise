#include<vector>
#include<unordered_map>
#include<queue>

using namespace std;

// 法1：广搜 + 预处理
class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        // 1. 建立串和index之间的哈希关系
        unordered_map<string, int> umap;
        int n = bank.size();
        for (int i = 0; i < n; i++) {
            umap[bank[i]] = i;
        }
        if (umap.find(startGene) == umap.end()) {   // startGene不在bank中，否则bank中原本就有startGene
            umap[startGene] = n;
            bank.push_back(startGene);
        }
        // 特殊情况判断：如果endGene不在umap中，那么直接返回不可能
        if (umap.find(endGene) == umap.end()) {
            return -1;
        }

        // 2. 对bank进行预处理，找到与他们只有一个字符不同的所有的串
        int n2 = bank.size();
        vector<vector<string>> dictionary(n2, vector<string>());
        for (int i = 0; i < n2; i++) {
            int idx = umap[bank[i]];
            for (int j = 0; j < n2; j++) {
                if (i == j) continue;
                int differNum = 0;
                for (int k = 0; k < 8; k++) {
                    if (bank[i][k] != bank[j][k]) {
                        differNum++;
                    }
                    if (differNum == 2) break;
                }
                if (differNum == 1) dictionary[idx].push_back(bank[j]);
            }
        }

        // 3. 进行广搜
        queue<string> q;
        q.push(startGene);
        int currChoice = 1;
        int step = 1;
        vector<int> visited(n2, 0);
        visited[umap[startGene]] = 1;
        while (!q.empty()) {
            int nextChoice = 0;
            // 将当前队列中的所有元素的所有相邻元素全都加入队列中
            for (int i = 0; i < currChoice; i++) {
                string currString = q.front();
                q.pop();
                for (int j = 0; j < dictionary[umap[currString]].size(); j++) {
                    string pushStr = dictionary[umap[currString]][j];
                    if (pushStr == endGene) return step;
                    if (visited[umap[pushStr]] == 0) {
                        q.push(pushStr);
                        nextChoice++;
                        visited[umap[pushStr]] = 1;
                    }
                }
            }
            currChoice = nextChoice;
            step++;
        }
        return -1;
    }
};
