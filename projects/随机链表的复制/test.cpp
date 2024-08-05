#include <cstddef>
#include<vector>
#include<unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        vector<Node*> vec;
        Node *p = head, *newHead = new Node(0), *newTail = newHead;
        unordered_map<Node*, int> umap;
        int index = 0;
        while(p->next != nullptr) {
            Node* newNode = new Node(p->val);
            newTail->next = newNode;
            newTail = newNode;
            vec.push_back(newTail);
            umap[p] = index++;
            p = p->next;
        }
        p = head;
        Node* currNode = newHead->next;
        while(p->next != nullptr) {
            // 找到p所指的结点的Index，进而找到数组中的对应指针
            currNode->random = vec[umap[p->random]];
            currNode = currNode->next;
            p = p->next;
        }
    }
};
