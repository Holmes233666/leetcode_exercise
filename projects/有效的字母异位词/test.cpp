#include<string>
#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> umap;
        int n = s.size(), m = t.size();
        if (m != n) return false;
        for (int i = 0; i < n; i++) {
            umap[s[i]]++;
        }
        for (int j = 0; j < m; j++) {
            if (umap.find(t[j]) == umap.end()) return false;
            umap[t[j]]--;
            if (umap[t[j]] == 0) umap.erase(t[j]);
        }
        return true;
    }
};
