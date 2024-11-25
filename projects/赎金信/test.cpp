#include<unordered_map>
#include<string>

using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        // 先扫描一遍magazine，将所有单词放入哈希表
        unordered_map<char, int> umap;
        int m = magazine.size(), n = ransomNote.size();
        for (int i = 0; i < m; i++) {
            umap[magazine[i]]++;
        }
        for (int j = 0; j < n; j++) {
            if (umap.find(ransomNote[j]) == umap.end() || umap[ransomNote[j]] == 0) return false;
            umap[ransomNote[j]]--;
        }
        return true;
    }
};
