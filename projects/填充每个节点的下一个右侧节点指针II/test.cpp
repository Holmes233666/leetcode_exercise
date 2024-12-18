#include<queue>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) return root;
        queue<Node*> t_queue;
        t_queue.push(root);
        while (!t_queue.empty()) {
            Node* currNode = t_queue.front();
            int num = t_queue.size();   // 记录目前队列中有多少个结点，即这一层的节点数
            for (int i = 0; i < num; i++) {
                t_queue.pop();
                if (currNode->left != nullptr) t_queue.push(currNode->left);
                if (currNode->right != nullptr) t_queue.push(currNode->right);
                if (i != num-1) {   // 如果不是最后一个节点，那么next指针指向队列的第一个元素
                    currNode->next = t_queue.front();
                }else { // 如果是这一层的最后一个节点，那么next结点应该指向nullptr
                    currNode->next = nullptr;
                }
                currNode = t_queue.front();
            }
        }
        return root;
    }
};