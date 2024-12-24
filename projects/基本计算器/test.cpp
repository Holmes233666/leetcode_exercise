#include<stack>

using namespace std;


class Solution {
public:
    int calculate(string s) {
        stack<int> ops;
        ops.push(1);    // 初始符号为正号
        int res = 0, sign = 1;            // 最后结果，和初始符号位
        for (int i = 0; i < s.size(); ) {
            if (s[i] == '(') {
                ops.push(sign);
                i++;
            }else if (s[i] == ')') {
                ops.pop();
                sign = ops.top();
                i++;
            }else if (s[i] == '+') {
                sign = ops.top();
                i++;
            }else if (s[i] == '-') {
                sign = -ops.top();
                i++;
            }else if (s[i] == ' '){
                i++;
            }else {
                long currNum = 0;
                while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                    currNum = currNum * 10 + s[i] - '0';
                    i++;
                }
                res += sign * currNum;
            }
        }
        return res;
    }
};