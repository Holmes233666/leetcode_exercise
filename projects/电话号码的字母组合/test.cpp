#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    vector<vector<char>> num2letter = {{},{},{'a','b','c'},{'d','e','f'},{'g','h','i'},
    {'j','k','l'}, {'m','n','o'}, {'p','q','r', 's'}, {'t','u','v'},
        {'w','x','y', 'z'}};
    vector<string> res;
    vector<string> letterCombinations(string digits) {
        vector<int> idxes;
        string currRes;
        for (int i = 0; i < digits.size(); i++) {
            idxes.push_back(digits[i]-'0');
        }
        // 对digits进行深搜
        DFS(currRes, idxes, 0);
        return res;
    }
    void DFS(string& currRes, vector<int>& indxes, int indexVecindex) {
        if (indexVecindex == indxes.size()) {
            res.push_back(currRes);
            return;
        }
        vector<char> currVector = num2letter[indxes[indexVecindex]];
        for (int i = 0; i < currVector.size(); i++) {
            currRes.push_back(currVector[i]);
            DFS(currRes, indxes, indexVecindex+1);
            currRes.pop_back();
        }
    }
};