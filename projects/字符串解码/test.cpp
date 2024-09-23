#include<string>
#include<stack>
#include<queue>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<int> nums;
        stack<string> strs;
        for (int i = 0; i < s.size();) {
            int tempNum = 0;
            if (s[i] >= '0' && s[i] <= '9') {
                while (s[i] >= '0' && s[i] <= '9') {
                    tempNum = tempNum * 10 + s[i] - '0';
                    i++;
                }
                nums.emplace(tempNum);
            }else {
                string tempStr;
                if (s[i] == '[') {
                    tempStr.push_back('[');
                    strs.emplace(tempStr);
                    i++;
                }else if (s[i] == ']') {
                    while (!strs.empty() && strs.top() != "[") {
                        tempStr = strs.top() + tempStr;
                        strs.pop();
                    }
                    // 弹出'['
                    if (!strs.empty()) strs.pop();
                    // tempStr要重复num次
                    int num = nums.top();
                    nums.pop();
                    string newStr = tempStr;
                    while (--num) {
                        newStr += tempStr;
                    }
                    // 新的字符串压栈
                    strs.emplace(newStr);
                    i++;
                }else { // 遇到的是字符，直接压栈
                    string tempStr;
                    tempStr.push_back(s[i]);
                    strs.emplace(tempStr);
                    i++;
                }
            }
        }
        // 获得了所有的字符后，将字符串取出，进行连接。
        string res;
        while (!strs.empty()) {
            res = strs.top() + res;
            strs.pop();
        }
        return res;
    }
};

