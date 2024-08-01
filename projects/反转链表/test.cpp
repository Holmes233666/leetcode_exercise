#include<iostream>
#include<stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 方法1： 栈
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;
        stack<ListNode*> nodeStack; // 存储指针
        ListNode* p = head;
        // 放入栈
        while(p != nullptr) {
            nodeStack.push(p); // 存储指针
            p = p->next;
        }
        // 从栈中取出节点
        p = nodeStack.top();
        ListNode* tempNode = p;
        nodeStack.pop();
        while (!nodeStack.empty()) {
            ListNode* q = nodeStack.top();
            nodeStack.pop();
            p->next = q;
            p = q;
        }
        p->next = nullptr; // 最后一个节点的 next 设为 nullptr
        return tempNode;
    }
};

// 方法2： pre指针记录
class Solution2 {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;
        ListNode *curr = head->next, *pre = head;
        pre->next = nullptr;
        while (curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
        }
        return pre;
    }
};

class Solution3 {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *curr = head, *pre = nullptr;
        while (curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
        }
        return pre;
    }
};

int  main() {
    return 0;
}

