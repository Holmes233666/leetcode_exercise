#include<string>
#include<vector>

using namespace std;

class Solution {
public:
    vector<vector<string>> res;
    vector<vector<string>> partition(string s) {
        vector<string> currRes;
        int start = 0;
        DFS(currRes, start, s);
        return res;
    }

    void DFS(vector<string>& currRes, int start, string& s) {
        // 到最后一个字符了
        if (start == s.size()) {
            res.push_back(currRes);
            return;
        }
        if (start <= s.size()-1) {
            string tempString = "";
            for (int i = start; i < s.size(); i++) {
                tempString.push_back(s[i]);
                if (!judge(tempString)) continue;
                currRes.push_back(tempString);
                DFS(currRes, i+1, s);
                currRes.pop_back();
            }
        }
    }

    bool judge(string& s) {
        // 判断是不是回文串
        int left = 0, right = s.size()-1;
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};


// 动态规划，预先处理s[i-j]是不是回文串，节省判断时间
class Solution2 {
public:
    vector<vector<string>> res;
    vector<vector<bool>> f;
    vector<vector<string>> partition(string s) {
        vector<string> currRes;
        f = vector<vector<bool>> (s.size(), vector<bool>(s.size(), true));
        // 回文串的预判断，注意边界条件
        for (int i = s.size()-2; i >= 0; i--) {
            for (int j = i + 1; j < s.size(); j++) {
                f[i][j] = f[i+1][j-1] && (s[i] == s[j]);
            }
        }
        int start = 0;
        DFS(currRes, start, s);
        return res;
    }

    void DFS(vector<string>& currRes, int start, string& s) {
        // 到最后一个字符了
        if (start == s.size()) {
            res.push_back(currRes);
            return;
        }
        if (start <= s.size()-1) {
            string tempString = "";
            for (int i = start; i < s.size(); i++) {
                tempString.push_back(s[i]);
                if (!f[start][i]) continue;
                currRes.push_back(tempString);
                DFS(currRes, i+1, s);
                currRes.pop_back();
            }
        }
    }
};


