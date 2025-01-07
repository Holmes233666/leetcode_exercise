#include<vector>
#include<unordered_map>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


// 深度优先搜索
class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<int, Node*> ump;
        Node* res = nullptr;
        dfs_create(node, res, ump);
        return res;
    }

    // newNode应该在搜索完成结束后加入数组中，否则没法在数组中访问到
    void dfs_create(Node* orignNode, Node* &newNode, unordered_map<int, Node*>& umap) {
        if (orignNode != nullptr) {
            newNode = new Node(orignNode->val);
            umap[newNode->val] = newNode;
            vector<Node*> currNextVec = orignNode->neighbors;
            for (int i = 0; i < currNextVec.size(); i++) {
                if (umap.find(currNextVec[i]->val) == umap.end()) { // 没找到
                    Node* nextNode;
                    dfs_create(currNextVec[i], nextNode, umap);
                    umap[newNode->val]->neighbors.push_back(nextNode);
                }else{
                    umap[newNode->val]->neighbors.push_back(umap[currNextVec[i]->val]);
                }
            }
        }
    }
};
