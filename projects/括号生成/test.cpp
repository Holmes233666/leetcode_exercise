#include<vector>
#include<stack>

using namespace std;

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

int main() {
    int n = 3;
    Solution s;
    s.generateParenthesis(n);
    return 0;
}