#include<unordered_map>
#include<sstream>
#include<string>

using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        stringstream ss(s);
        vector<string> words;
        string word;
        unordered_map<char, string> umap1;
        unordered_map<string, char> umap2;
        int n = pattern.size();
        while (ss >> word) {
            words.push_back(word);
        }
        for (int i = 0, j = 0; i < n; i++, j++) {
            if (umap1.find(pattern[i]) == umap1.end() && umap2.find(words[j]) == umap2.end()) { // 没有对应关系
                umap1[pattern[i]] = words[j];
                umap2[words[j]] = pattern[i];
            }else if ((umap1.find(pattern[i]) != umap1.end() && umap1[pattern[i]] == words[j])
                || (umap2.find(words[j]) != umap2.end() && umap2[words[j]] == pattern[i])) {
                return false;
            }
        }
        return true;
    }
};
