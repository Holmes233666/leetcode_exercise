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

// class Trie {
// public:
//     vector<Trie*> child;
//     bool isEnd;
//     Trie() {
//         child = vector<Trie*>(26);
//         isEnd = false;
//     }
//
//     void insert(string word) {
//         Trie* t = this;
//         int index = 0;
//         while (index < word.length()) {
//             int i = word[index++] - 'a';
//             if (t->child[i] == nullptr) {
//                 t->child[i] = new Trie();
//             }
//             t = t->child[i];
//         }
//         t->isEnd = true;
//     }
//
//     bool search(string word) {
//         // 从首字母开始依次向下搜索
//         int index = 0;
//         Trie* t = this;
//         while (index < word.length()) {
//             int i = word[index] - 'a';
//             if (t->child[i] == nullptr) return false;
//             t = t->child[i];
//             index++;
//         }
//         if (t->isEnd == false) return false;
//         return true;
//     }
//
//     bool startsWith(string prefix) {
//         // 从首字母开始依次向下搜索
//         int index = 0;
//         Trie* t = this;
//         while (index < prefix.length()) {
//             int i = prefix[index] - 'a';
//             if (t->child[i] == nullptr) return false;
//             t = t->child[i];
//             index++;
//         }
//         return true;
//     }
// };

class Node {
public:
    vector<Node*> children;
    bool isEnd;

    Node() {
        children = vector<Node*>(26, nullptr);
        isEnd = false; // 默认不是单词的结尾，如果是的话需要修改标记位。
    }

    Node(char val) {
        children = vector<Node*>(26, nullptr);
        children[val - 'a'] = new Node();
        children[val - 'a']->isEnd = false;
        isEnd = false;
    }
};

class Trie {
public:
    Node* head;

    Trie() {
        head = new Node();
    }

    void insert(string word) {
        int n = word.size();
        Node *currNode = head;
        for (int i = 0; i < n; i++) {
            if (currNode == nullptr) {
                currNode = new Node(word[i]);
            }
            if (currNode->children[word[i]-'a'] == nullptr){    // 存在这个结点，但是之前没字母。（不会对等于2的情况进行修改）
                currNode->children[word[i]-'a'] = new Node();
            }
            if (i == n-1) {
                currNode->children[word[i]-'a']->isEnd = true;   // 有到该字母为止的单词
            }
            currNode = currNode->children[word[i] - 'a'];
        }
    }

    bool search(string word) {
        // 对head开始进行向下检索
        int n = word.size();
        Node* currNode = head;
        for (int i = 0; i < n; i++) {
            if (currNode == nullptr) return false;
            if (currNode->children[word[i]-'a'] == nullptr) return false;
            if (i == n-1 && currNode->children[word[i]-'a']->isEnd == true) {
                return true;
            }
            currNode = currNode->children[word[i] - 'a'];
        }
        return false;
    }

    bool startsWith(string prefix) {
        // 对head开始进行向下检索
        int n = prefix.size();
        Node* currNode = head;
        for (int i = 0; i < n; i++) {
            if (currNode == nullptr) return false;
            if (currNode->children[prefix[i]-'a'] == nullptr) return false;
            if (i == n-1 && currNode->children[prefix[i]-'a'] != 0){
                return true;
            }
            currNode = currNode->children[prefix[i]-'a'];
        }
        return false;
    }
};
