#include<vector>

using namespace std;

class WordDictionary {
public:
    WordDictionary* w;
    vector<WordDictionary*> child;
    bool isEnd;

    WordDictionary() {
        child = vector<WordDictionary*>(26);
        isEnd = false;
    }

    void addWord(string word) {
        int n = word.size();
        WordDictionary* curr = this;
        for (int i = 0; i < n; i++) {
            int idx = word[i] - 'a';
            if (curr->child[idx] == nullptr) {
                curr->child[idx] = new WordDictionary();
            }
            curr = curr->child[idx];
        }
        curr->isEnd = true;
    }

    bool search(string word) {
        return dfs(0, word, this);
    }

    bool dfs(int idx, string& word, WordDictionary* curr) {
        if (idx == word.size() && curr->isEnd == true) {
            return true;
        }
        if (idx == word.size() && curr->isEnd == false) {
            return false;
        }
        if (word[idx] == '.') { // 进行深搜
            // 尝试每个字母
            for (int i = 0; i < 26; i++) {
                // 任意一个单词非空，进行深搜
                if (curr->child[i] != nullptr) {
                    bool flag = dfs(idx+1, word, curr->child[i]);
                    if (flag) return true;
                }
            }
            return false;
        }else { // word[idx] 是一个单词
            int i = word[idx] - 'a';
            if (curr->child[i] == nullptr) return false;
            return dfs(idx+1, word, curr->child[i]);
        }
        return false;
    }
};

