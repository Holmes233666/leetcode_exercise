#include<vector>

using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int resNum = 0;
        dfs(0, n, res, resNum);
        return resNum;
    }

    void dfs(int idx, int n, vector<vector<int>>& res, int& resNum) {
        if (idx == n) {
            resNum++;
            return;
        }
        for (int i = 0; i < n; i++) {
            if (judge(res, idx, i, n)) {
                res[idx][i] = 1;
                dfs(idx+1, n, res, resNum);
                res[idx][i] = 0;
            }
        }
    }

    bool judge(vector<vector<int>>& res, int idx, int pos, int n) {
        for (int i = 0; i < idx; i++) {
            if (res[i][pos] == 1) return false;
            for (int j = 0; j < n; j++) {
                if (res[i][j] == 1 && abs(i-idx) == abs(idx-pos)) return false;
            }
        }
        return true;
    }
};
