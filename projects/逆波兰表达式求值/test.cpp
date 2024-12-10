#include<vector>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<int> myStack;
        int n = tokens.size();
        for (int i = 0; i < n; i++) {
            string currToken = tokens[i];
            if (currToken == "+" || currToken == "-" || currToken == "*" || currToken == "/") {
                int secondNum = myStack[myStack.size()-1];
                myStack.pop_back();
                int firstNum = myStack[myStack.size()-1];
                myStack.pop_back();
                if (currToken == "+") {
                    myStack.push_back(firstNum + secondNum);
                }else if (currToken == "-") {
                    myStack.push_back(firstNum - secondNum);
                }else if (currToken == "*") {
                    myStack.push_back(firstNum * secondNum);
                }else {
                    myStack.push_back(firstNum / secondNum);
                }
            }else {
                myStack.push_back(stoi(currToken));
            }
        }
        return myStack[myStack.size()-1];
    }
};
