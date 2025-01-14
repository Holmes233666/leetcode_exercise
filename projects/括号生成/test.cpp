#include<vector>
#include<stack>

using namespace std;

// 法1：压栈时判断是否可以放入该括号
class Solution {
public:
    stack<char> currStack;
    vector<string> res;
    vector<char> brackets = {'(', ')'};
    vector<string> generateParenthesis(int n) {
        string s = "";
        DFS(0, n*2, s);
        return res;
    }

    void DFS(int currBrackNum, int n, string& s) {
        if (currBrackNum == n && currStack.empty()) {
            res.push_back(s);
            return;
        }else if (currBrackNum == n) return;
        for (int i = 0; i < brackets.size(); i++) {
            if (!tacleStack(currStack, brackets[i])) continue;
            // 修改字符串
            s.push_back(brackets[i]);
            DFS(currBrackNum+1, n, s);
            s.pop_back();
            // 分两种情况：如果是左括号'('：弹栈；如果是右括号')'：那么压栈一个'('
            if (brackets[i] == '(') {
                currStack.pop();
            }else {
                currStack.emplace('(');
            }

        }
    }

    bool tacleStack(stack<char>& s, char currBracket) {
        // 修改栈
        if (currBracket == '(') {
            s.emplace('(');
            return true;
        }
        // 是')'，栈顶一定是左括号才对
        if (!s.empty() && s.top() == '(') {
            // 弹出左括号
            s.pop();
            return true;
        }
        // 是右括号，如果是空栈或者栈顶不是左括号，那么不满足条件，不用压栈
        return false;
    }
};


// 法2：暴力解法，深搜完进行括号正确性判断，高时间复杂度
class Solution2 {
public:
    vector<string> res;
    vector<char> brackets = {'(', ')'};
    vector<string> generateParenthesis(int n) {
        string s = "";
        DFS(0, n*2, s);
        return res;
    }

    void DFS(int currBrackNum, int n, string& s) {
        if (currBrackNum == n) {
            if (judgeStack(s)) {
                res.push_back(s);
                return;
            }else return;   // 错误压栈结果
        }
        for (int i = 0; i < brackets.size(); i++) {
            s.push_back(brackets[i]);
            DFS(currBrackNum+1, n, s);
            s.pop_back();
        }
    }

    bool judgeStack(string& s) {
        stack<char> charStack;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                charStack.emplace(s[i]);
                continue;
            }
            if (!charStack.empty() && charStack.top() == '(') {
                charStack.pop();
            }else {
                return false;
            }
        }
        if (charStack.empty()) return true;
        return false;
    }
};

// 法1：第二次刷
class Solution3 {
public:
    vector<string> generateParenthesis(int n) {
        stack<char> bra_s;
        vector<string> res;
        vector<char> brackets = {'(', ')'};
        string currStr = "";
        dfs(2*n, currStr, res, brackets, bra_s);
        return res;
    }

    void dfs(int n, string& currStr, vector<string>& res, vector<char>& brackets, stack<char>& bra_s) {
        if (n == currStr.size() && bra_s.empty()) {
            res.push_back(currStr);
            return;
        }else if (n == currStr.size()) {
            return;
        }
        for (int i = 0; i < brackets.size(); i++) {
            // 尝试放入括号
            if (judgeSta(brackets[i], bra_s, n/2)) {
                currStr.push_back(brackets[i]);
                if (brackets[i] == '(') {
                    bra_s.push('(');
                }else{
                    bra_s.pop();
                }
                dfs(n, currStr, res, brackets, bra_s);
                currStr.pop_back();
                if (brackets[i] == '(') {
                    bra_s.pop();
                }else{
                    bra_s.push('(');
                }
            }
        }
    }

    bool judgeSta(char bracket, stack<char>& bra_s, int n) {
        if (bra_s.size() == n && bracket == '(') return false;
        if (bra_s.empty() && bracket == ')') return false;
        return true;
    }
};

int main() {
    int n = 3;
    Solution s;
    s.generateParenthesis(n);
    return 0;
}