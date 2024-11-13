#include<vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        // 字母以4个为一组进行排列
        if (numRows == 1) return s;
        vector<int> toput;

        int maxRowIdx = numRows - 1;
        for (int i = 0; i < (numRows-1)*2; i++) {
            if (i < numRows) {
                toput.push_back(i);
            }else {
                toput.push_back(--maxRowIdx);
            }
        }

        int toPutSize = toput.size();

        vector<vector<int>> res(numRows, vector<int>());
        string resStr;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            res[toput[i % toPutSize]].push_back(s[i]);
        }

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < res[i].size(); j++) {
                resStr.push_back(res[i][j]);
            }
        }

        return resStr;
    }
};