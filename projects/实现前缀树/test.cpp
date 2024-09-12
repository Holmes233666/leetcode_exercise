#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>

using namespace std;

// 可能超时间复杂度的做法
// class Trie {
// public:
//     unordered_map<string, int> umap;
//     string cmp;
//     Trie() {
//
//     }
//
//     void insert(string word) {
//         umap[word]++;
//     }
//
//     bool search(string word) {
//         if (umap.find(word) != umap.end()) return true;
//         return false;
//     }
//
//     bool startsWith(string prefix) {
//         for (auto term:umap) {
//             string word = term.first;
//             int index = 0;
//             while (index < word.length() && index < prefix.length()) {
//                 if (word[index] != prefix[index]) break;
//                 index++;
//             }
//             if (index == prefix.length()) return true;
//         }
//         return false;
//     }
// };

class Trie {
public:
    vector<Trie*> child;
    bool isEnd;
    Trie() {
        child = vector<Trie*>(26);
        isEnd = false;
    }

    void insert(string word) {
        Trie* t = this;
        int index = 0;
        while (index < word.length()) {
            int i = word[index++] - 'a';
            if (t->child[i] == nullptr) {
                t->child[i] = new Trie();
            }
            t = t->child[i];
        }
        t->isEnd = true;
    }

    bool search(string word) {
        // 从首字母开始依次向下搜索
        int index = 0;
        Trie* t = this;
        while (index < word.length()) {
            int i = word[index] - 'a';
            if (t->child[i] == nullptr) return false;
            t = t->child[i];
            index++;
        }
        if (t->isEnd == false) return false;
        return true;
    }

    bool startsWith(string prefix) {
        // 从首字母开始依次向下搜索
        int index = 0;
        Trie* t = this;
        while (index < prefix.length()) {
            int i = prefix[index] - 'a';
            if (t->child[i] == nullptr) return false;
            t = t->child[i];
            index++;
        }
        return true;
    }
};

int main() {
    return 0;
}