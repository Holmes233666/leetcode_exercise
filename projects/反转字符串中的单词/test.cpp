#include<vector>

using namespace std;

// 法1：双指针
class Solution {
public:
    string reverseWords(string s) {
        // 从最后一个字符往前扫，直到找到下一个空格
        int n = s.size(), left = n-1;
        vector<string> res;
        // 首先找到第一个非空格的末尾字母
        for (;left >= 0 && s[left] == ' '; left--) {
        }
        // 然后找到第一个非空格的开头字母
        int leftMin = 0;
        for (;leftMin < n && s[leftMin] == ' '; leftMin++) {

        }
        string s2;
        for (int right = left; left >=leftMin ; ) {
            if (s[left] == ' ' || left == leftMin) {   // left遇到空格了，说明一个单词结束了
                int start = left + 1;
                if (left == leftMin) {
                    start = left;
                }
                // 将一个单词放入
                while (start <= right) {
                    s2.push_back(s[start]);
                    start++;
                }
                if (left == leftMin) {
                    break;
                }
                s2.push_back(' ');
                // 对于右指针，跳过left前方的所有空格
                right = left;
                while (s[right] == ' ' && right >= 0) {
                    right--;
                }
                left = right;
            }else {
                left--;
            }
        }
        return s2;
    }
};

// 法2：