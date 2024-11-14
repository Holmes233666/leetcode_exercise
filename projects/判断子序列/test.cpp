#include<string>
#include<vector>

using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int currMatch = 0;
        for (int i = 0; i < s.size(); i++) {
            int  j = currMatch;
            for (; j < t.size(); j++) {
                if (s[i] == s[j]) {
                    break;
                }
            }
            if (s[i] == s[j]) {
                currMatch = j + 1;
                i++;
            }else {
                return false;
            }
        }
        return true;
    }
};