#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // 题目保证了串非空
        if (p.size() > s.size()) return {};
        vector<int> res;
        // 将子串p中所有的字符放入map, key是字母，value是该字母在串p中出现次数
        unordered_map<char, int> umap;
        for (char c : p) {
            umap[c]++;
        }
        // 另外创建一个set，有所有待匹配的字母
        unordered_map<char, int> umap_copy(umap);
        // 从串s的第一个字符开始，进行匹配。
        for (int left = 0, right = left; left < s.size();) {
            //cout << "current left is: " << left << endl;
            while(left < s.size() && right < s.size() && right - left + 1 <= p.size()) {
                // 遇到了新的字符: 该字符不在p中，肯定要跳过
                if (umap[s[right]] == 0) {
                    left = right + 1;
                    // 重置umap和右指针
                    umap_copy = umap;
                    right = left;
                    break;
                }else if(umap[s[right]] != 0 && umap_copy[s[right]] <= 0) { // 这个字母已经匹配完了
                    while(umap_copy[s[right]] <= 0) {
                        umap_copy[s[left]]++;
                        left++;
                    }
                    break;
                }else if (umap[s[right]] != 0 && umap_copy[s[right]] != 0){  // 该字符在p中，有可能构成子串
                    // 进一步检查是不是本轮第一次遇到这个字符，如果重复遇到，那么umap_copy[s[i]]递减
                    umap_copy[s[right]]--;
                    // 到了末尾，且匹配，那么说明找到了正确答案
                    if (right - left + 1 == p.size()) {
                        // 记录答案
                        res.push_back(left);
                        // umap不应该重置，而是仅对移动的最左侧字母做+1操作，表示待匹配次数增加
                        umap_copy[s[left]]++;
                        right++;
                        left += 1;
                        break;
                    }
                    right++;
                } 
            }
            if (right >= s.size()) {
                return res;
            }
        }
        return res;
    }
};

class Solution2 {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size(), m = p.size();
        vector<int> res;
        unordered_map<char, int> umap;
        // 记录p的字典
        for (int i = 0; i < m; i++) {
            umap[p[i]]++;
        }
        int charNum = umap.size();
        unordered_map<char, int> currMap;
        // 滑动窗口
        for (int left = 0, right = 0; right < n; right++) {
            // 当前字符
            char currChar = s[right];
            while(right-left+1 > m) {  // 扩展左边界
                currMap[s[left]]--;
                if (currMap[s[left]] == umap[s[left]]-1) charNum--;
                left++;
            }
            // 扩展右边界
            currMap[currChar]++;
            if (currMap[currChar] == umap[currChar]) {
                charNum--;
            }
            if (charNum == 0) {
                res.push_back(left);
            }
        }
        return res;
    }
};


int main() {
    string a = "abab", b = "ab";
    Solution solution;
    vector<int> res = solution.findAnagrams(a, b);
    cout << "The size of res is: " << res.size() << endl;
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    return 0;
}