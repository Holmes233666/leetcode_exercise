#include<iostream>
#include<stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;
        stack<ListNode> nodeStack;
        ListNode* p = head;
        // 放入栈
        while(p != nullptr) {
            nodeStack.emplace(*p);
            p = p->next;
        }
        // 从栈中取出节点
        p = &(nodeStack.top());
        ListNode* tempNode = p;
        nodeStack.pop();
        while (!nodeStack.empty()) {
            ListNode* q = &(nodeStack.top());
            nodeStack.pop();
            p->next = q;
            p = q;
        }
        return tempNode;
    }
};

int  main() {
    return 0;
}

