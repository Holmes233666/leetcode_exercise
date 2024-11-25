#include<vector>
#include<unordered_map>

using namespace std;
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int n = s.size();
        unordered_map<char, char> umap1, umap2;
        for (int i = 0, j = 0; i < n; i++, j++) {
            if (umap1.find(s[i]) == umap1.end() && umap2.find(t[j]) == umap2.end()) {    // 如果没有映射关系
                umap1[s[i]] = t[j];  // 将s[i]映射到t[j]
                umap2[t[j]] = s[i];
            }else if ((umap1.find(s[i]) != umap1.end() && umap1[s[i]] != t[j])
                || (umap2.find(t[j]) != umap2.end() && umap2[t[j]] != s[i])) { // 有映射关系且对应不上 or 已经有别的字母与tj建立了关系
                return false;
            }
        }
        return true;
    }
};
