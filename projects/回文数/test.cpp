#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        if (x >= 0 && x <= 9) return true;
        // 转换为string判断
        string res;
        while(x != 0) {
            int modNum = x % 10;
            x /= 10;
            res.push_back('0'+modNum);
        }
        int n = res.size();
        for (int i = 0, j = res.size()-1; i < n && j >= 0; i++, j--) {
            if (res[i] != res[j]) return false;
        }
        return true;
    }
};
