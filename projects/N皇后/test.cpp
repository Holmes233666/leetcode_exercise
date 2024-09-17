#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    vector<vector<string>> res;
    vector<vector<string>> solveNQueens(int n) {
        vector<int> currRes;
        DFS(currRes, 0, n);
        return res;
    }

    void DFS(vector<int>& currRes, int currIndex, int n) {
        if (currIndex == n) {
            loc2str(currRes);
            return;
        }
        // 枚举该皇后在该列的个位置
        for (int i = 0; i < n; i++) {
            if (!judge(currIndex, i, currRes)) continue;
            currRes.push_back(i);
            DFS(currRes, currIndex+1, n);
            currRes.pop_back();
        }
    }

    bool judge(int currI, int currJ, vector<int>& currRes) {
        for (int i = 0; i < currRes.size(); i++) {
            int cmpI = i, cmpJ = currRes[i];
            if (cmpI == currI || cmpJ == currJ || abs(cmpI-currI) == abs(cmpJ-currJ)) {
                return false;
            }
        }
        return true;
    }

    void loc2str(vector<int>& currRes) {
        vector<string> tempRes;
        for (int i = 0; i < currRes.size(); i++) {
            string s(currRes.size(), '.');
            s[currRes[i]] = 'Q';
            tempRes.push_back(s);
        }
        res.push_back(tempRes);
    }
};
