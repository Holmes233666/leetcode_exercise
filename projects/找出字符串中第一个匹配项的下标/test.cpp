#include<string>
#include<vector>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        vector<int> next;
        int m = haystack.size(), n = needle.size();
        getNext(needle, next);
        for (int i = 0, j = 0; i < m; ) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }else if (j > 0) {  // 不匹配
                j = next[j-1];
            }else { // 不匹配
                i++;
            }
            if (j == n) return i-j; // 如果到末尾都不匹配呢？
        }
        return -1;
    }

    void getNext(string& needle, vector<int>& next) {
        int n = needle.size();
        next.push_back(0);  // next[0] = 0;
        int prefix_len = 0;
        for(int i = 1; i < n; ) {
            if (needle[i] == needle[prefix_len]) {
                prefix_len++;
                next.push_back(prefix_len);
                i++;
            }else {
                if (prefix_len == 0) {
                    next.push_back(0);
                    i++;
                }else {
                    prefix_len = next[prefix_len - 1];  // 看看有没有更短的前后缀
                }
            }
        }
    }
};

class Solution2 {
public:
    int strStr(string haystack, string needle) {
        int res = haystack.find(needle);
        return res == haystack.npos ? -1 : res;
    }
};
