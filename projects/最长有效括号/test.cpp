#include<vector>
#include<stack>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<pair<char, int>> braketStack;
        int maxLen = 0, currLen = 0;
        int interrupt = 0;
        for (int i = 0; i < s.size();) {
            if (s[i] == '(') {
                braketStack.emplace('(', i);
                i++;
            }else {
                if (s[i] == ')' && braketStack.empty()) {
                    i++;
                    currLen = 0;
                    continue;
                }
                while (i < s.size() && s[i] == ')' && !braketStack.empty()) {
                    // cout << "curr i is: " << i << " curr bracket is: " << s[i] << endl;
                    braketStack.pop();
                    i++;
                    currLen += 2;
                    if (i == s.size() && !braketStack.empty() && braketStack.top().second + currLen >= i) currLen = i-braketStack.top().second-1;
                    maxLen = max(currLen, maxLen);
                }
            }
        }
        return maxLen;
    }
};

class Solution2 {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if (n == 0 || n == 1) return 0;
        vector<int> f = vector<int>(n, 0);
        if (1 < n && s[1] == ')' && s[0] == '(') f[1] = 2;
        int maxLen = f[1];
        for (int i = 2; i < n; i++) {
            if (s[i] == '(') {
                f[i] = 0;
            }else { // s[i] == ')'
                if (s[i-1] == '(') {
                    f[i] = f[i-2] + 2;
                }else {
                    if (f[i-1] == 0 && s[i-1] == ')') {
                        f[i] = 0;
                    }else if (f[i-1] == 0 && s[i-1] == '(') {
                        f[i] = f[i-2] + 2;
                    }else {
                        if (i-f[i-1]-1 < 0 || (i-f[i-1]-1 >= 0 && s[i-f[i-1]-1] == ')')) {
                            f[i] = 0;
                        }else if (s[i-f[i-1]-1] == '(') {
                            if (i-f[i-1]-1 == 0) {
                                f[i] = f[i-1] + 2;
                            }else if (s[i-f[i-1]-1-1] == '(' ) {
                                f[i] = f[i-1]+2;
                            }else if (s[i-f[i-1]-1-1] == ')') {
                                f[i] = f[i-f[i-1]-1-1] + f[i-1] + 2;
                            }
                        }
                    }
                }
            }
            maxLen = max(f[i], maxLen);
        }
        return maxLen;
    }
};