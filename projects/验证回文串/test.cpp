#include<string>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();
        for(int i = 0, j = n-1; i <= j; ) {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                s[i] = s[i] + 32;
            }
            if (s[j] >= 'A' && s[j] <= 'Z') {
                s[j] = s[j] + 32;
            }

            // 如果不是字母/数字，那么应该跳过
            if ((s[i] < 'a' || s[i] > 'z') && (s[i] < '0' || s[i] > '9')) {
                i++;
                continue;
            }
            if ((s[j] < 'a' || s[j] > 'z') && (s[j] < '0' || s[j] > '9')) {
                j--;
                continue;
            }
            if (s[i] != s[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};