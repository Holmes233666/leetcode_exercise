#include<string>
#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
#include <utility> 

using namespace std;

// 滑动窗口+umap + queue： 使用了队列，空间复杂度较高（队列是用来记录最新的有效的字母及其下标的，以快速定位到这个字母）
// 滑动窗口+umap + queue： 使用了队列，空间复杂度较高（队列是用来记录最新的有效的字母及其下标的，以快速定位到这个字母）
class Solution {
public:
    string minWindow(string s, string t) {
        // 特殊情况处理
        if (t.size() > s.size())
            return "";
        // 一般情况处理
        queue<pair<char, int>> q;
        unordered_map<char, int> c_umap;

        // 先把所有待匹配字母放进数组
        for (char c : t) {
            c_umap[c]++;
        }

        // 辅助函数来检查c_umap_cpy是否满足c_umap的条件
        auto matches = [&](unordered_map<char, int>& c_umap,
                           unordered_map<char, int>& c_umap_cpy) -> bool {
            for (auto& kv : c_umap) {
                if (!c_umap_cpy.count(kv.first) or c_umap_cpy[kv.first] < kv.second) {
                    return false;
                }
            }
            return true;
        };

        unordered_map<char, int> c_umap_cpy;

        int start = 0;
        int minLen = INT_MAX;
        string str;
        for (int left = 0, right = left; right < s.size(); right++) {
            // 是待匹配的字母
            if (c_umap.count(s[right])) {
                c_umap_cpy[s[right]]++;
                q.push(make_pair(s[right], right));
                left = q.front().second;
            }else{
                continue;
            }

            // 如果是匹配的串
            // 尝试收缩串，直到有字母不满足umap中的数值，此时，right++
            while (matches(c_umap, c_umap_cpy)) {
                // 如果是更短的子串
                if (minLen > right - left + 1) {
                    start = left;
                    minLen = right - left + 1;
                }
                c_umap_cpy[q.front().first]--;
                q.pop();
                left = q.front().second;
            }
        }
        return str = minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};

// 滑动窗口 + umap： 去掉队列，left逐个移动，不进行快速定位下一个
class Solution2 {
public:
    unordered_map<char, int> c_umap;
    unordered_map<char, int> c_umap_cpy;

    bool matches() {
        for (const auto &p: c_umap) {
            if (c_umap_cpy[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }
    string minWindow(string s, string t) {
        // 特殊情况处理
        if (t.size() > s.size()) return "";

        // 先把所有待匹配字母放进数组
        for (char c : t) {
            c_umap[c]++;
        }

        int minLen = INT_MAX;
        string str;
        int start = 0;
        for (int left = 0, right = left; right < s.size(); right++) {
            // 是待匹配的字母
            if (c_umap.count(s[right])) {
                c_umap_cpy[s[right]]++;
            }else{
                continue;
            }

            // 如果是匹配的串
            // 尝试收缩串，直到有字母不满足umap中的数值，此时，right++
            while (matches()) {
                // 如果是更短的子串
                if (minLen > right - left + 1) {
                    start = left;
                    minLen = right - left + 1;
                }
                if (c_umap_cpy.count(s[left])) c_umap_cpy[s[left]]--;
                left++;
            }
        }
        return str = minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};

// 队列 + 不使用哈希表比较
class Solution3 {
public:
    unordered_map<char, int> c_umap;
    unordered_map<char, int> c_umap_cpy;

    string minWindow(string s, string t) {
        // 特殊情况处理
        if (t.size() > s.size())
            return "";
        // 一般情况处理
        queue<pair<char, int>> q;

        // 先把所有待匹配字母放进数组
        for (char c : t) {
            c_umap[c]++;
        }

        string str;
        int minLen = INT_MAX;
        int cnt = 0;
        int start = 0;

        for (int left = 0, right = left; right < s.size(); right++) {
            // 是待匹配的字母
            if (c_umap.count(s[right])) {
                c_umap_cpy[s[right]]++;
                q.emplace(s[right], right);
                left = q.front().second;
                if (c_umap_cpy[s[right]] == c_umap[s[right]]) cnt++;
            }else{
                continue;
            }

            // 如果是匹配的串
            // 尝试收缩串，直到有字母不满足umap中的数值，此时，right++
            while (cnt == c_umap.size()) {
                // 如果是更短的子串
                if (minLen > right - left + 1) {
                    start = left;
                    minLen = right - left + 1;
                }
                c_umap_cpy[q.front().first]--;
                if (c_umap_cpy[q.front().first] < c_umap[q.front().first]) {
                    cnt--;
                }
                q.pop();
                left = q.front().second;
            }
        }
        return str = minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};

// 不进行哈希表比较
class Solution4 {
public:
    unordered_map<char, int> c_umap;
    unordered_map<char, int> c_umap_cpy;

    string minWindow(string s, string t) {
        // 特殊情况处理
        if (t.size() > s.size()) return "";

        // 先把所有待匹配字母放进数组
        for (char c : t) {
            c_umap[c]++;
        }

        int minLen = INT_MAX;
        string str;
        int start = 0;
        int cnt = 0;
        for (int left = 0, right = left; right < s.size(); right++) {
            // 是待匹配的字母
            if (c_umap.count(s[right])) {
                c_umap_cpy[s[right]]++;
                if (c_umap_cpy[s[right]] == c_umap[s[right]]) cnt++;
            }else{
                continue;
            }

            // 如果是匹配的串
            // 尝试收缩串，直到有字母不满足umap中的数值，此时，right++
            while (cnt == c_umap.size()) {
                // 如果是更短的子串
                if (minLen > right - left + 1) {
                    start = left;
                    minLen = right - left + 1;
                }
                if (c_umap.count(s[left])) {
                    c_umap_cpy[s[left]]--;
                    if (c_umap_cpy[s[left]] < c_umap[s[left]]) cnt--;
                }
                left++;
            }
        }
        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};

int main() {
    string s = "ADOBECODEBANC", t = "ABC";
    Solution4 solution;
    string res = solution.minWindow(s, t);
    cout << "The final result is: " << res << endl;
    return 0;
}