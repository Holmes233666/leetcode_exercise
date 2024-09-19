#include<iostream>
#include<stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> bracket_stack;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
                bracket_stack.emplace(s[i]);
                continue;
            }else {
                if (s[i] == ')') {
                    if (!bracket_stack.empty() && bracket_stack.top() == '(') {
                        bracket_stack.pop();
                        continue;
                    }
                    return false;
                }else if (s[i] == '}') {
                    if (!bracket_stack.empty() && bracket_stack.top() == '{') {
                        bracket_stack.pop();
                        continue;
                    }
                    return false;
                }else if (s[i] == ']') {
                    if (!bracket_stack.empty() && bracket_stack.top() == '[') {
                        bracket_stack.pop();
                        continue;
                    }
                    return false;
                }
            }
        }
        if (!bracket_stack.empty()) return false;
        return true;
    }
};

int main() {
    return 0;
}
