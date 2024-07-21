#include<vector>
#include<iostream>
#include<string>
#include<unordered_set>
#include<unordered_map>

using namespace std;

// 朴素想法
class Solution1 {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) return 0;
        // 尝试将每个字母作为一个子串的前缀，内部使用hash_map去重
        int maxLen = 1;
        for (int i = 0; i < s.size(); i++) {
            //cout << "-------i = " << i << " string[i] = "<<s[i]<< "-----"<<endl;
            unordered_set<char> stringBuffer;
            stringBuffer.insert(s[i]);
            int tempLength = 1;
            for(int j = i + 1; j < s.size(); j++) {
                auto it = stringBuffer.find(s[j]);
                // 找不到这个元素
                //cout << "j = " << j << " string[j] = "<<s[j]<< endl;
                if (it == stringBuffer.end()) {
                    //cout << "add " << s[j] << endl;
                    tempLength++;
                    maxLen = max(maxLen, tempLength);
                    stringBuffer.insert(s[j]);
                }else{  // 出现重复元素
                    //maxLen = max(maxLen, tempLength);
                    break;
                }
            }
        }
        return maxLen;
    }
};

// 滑动窗口，使用一个指针maxJumpTo保存一定不含重复子串的串
class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) return 0;
        // 尝试将每个字母作为一个子串的前缀，内部使用hash_map去重
        int maxLen = 1;
        int maxJumpTo = 1;
        unordered_set<char> stringBuffer;
        for (int i = 0; i < s.size(); i++) {
            stringBuffer.insert(s[i]);
            int tempLength = maxJumpTo - i;
            if (i == maxJumpTo) {
                tempLength = 1;
                maxJumpTo++;
            }
            for(int j = maxJumpTo; j < s.size(); j++) {
                auto it = stringBuffer.find(s[j]);
                // 无重复字母：
                if (it == stringBuffer.end()) {
                    stringBuffer.insert(s[j]);
                    tempLength++;
                    maxLen = max(maxLen, tempLength);
                }else{  // 出现重复元素
                    // buffer要重新设置：复制原来的buffer，但是去掉重复的元素
                    stringBuffer.erase(s[i]);
                    maxJumpTo = j;
                    break;
                }
            }
        }
        return maxLen;
    }
};


// 滑动窗口，进一步的想法，使用hash_map同时记录每个key的下标
class Solution3 {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) return 0;
        // 尝试将每个字母作为一个子串的前缀，内部使用hash_map去重
        unordered_map<char, int> hash_map;
        int maxLen = 1;
        for (int left = 0, right = left + 1; left < s.size(); ) {
            // key: 字符， value: 下标
            hash_map[s[left]] = left;
            // 右边的指针指的数一直不在map中，即没有重复字符
            while (right < s.size() && hash_map.find(s[right]) == hash_map.end()) {
                hash_map[s[right]] = right;                
                int tempLen = right - left + 1;
                maxLen = max (maxLen, tempLen);
                right++;
            }
            // while终止了：两种情况
            // a. 到串尾都没有重复的，那么后面的字母也不用枚举了，不会有比这个更长的串了
            if (right == s.size()) {
                return maxLen;
            }else{ // b. 没有到串尾，那么就是找到了重复的字符
                // 在重复字母前都不会有比现在的left - right更长的串了，left应该移动到hash_map[s[right]]+1处。
                int new_left = hash_map[s[right]] + 1;
                // erase应该擦除原来left和newleft之间的所有key
                for (int k = left; k < new_left; k++)
                    hash_map.erase(s[k]);
                left = new_left;
                // 连续两个相同字母
                if (right == left) right++;
                continue;
            }
        }
        return maxLen;
    }
};

int main() {
    Solution3 solution;
    string s = "pwwkew";
    int num = solution.lengthOfLongestSubstring(s);
    cout << "The Final Res Is: " << num << endl;
    return 0;
}