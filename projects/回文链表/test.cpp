#include<iostream>
#include<stack>
#include<vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 栈的实现
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // 如果是回文串，那么进栈和出栈的值是相同的
        ListNode *p;
        vector<int> inStackVec, outStackVec;
        stack<ListNode*> pstack;

        // 所有元素进栈
        while (p != nullptr) {
            pstack.push(p);
            inStackVec.push_back(p->val);
            p = p->next;
        }

        // 所有元素出栈
        while (!pstack.empty()) {
            ListNode *q = pstack.top();
            pstack.pop();
            outStackVec.push_back(q->val);
        }

        // 比较两个vector内容是否相同
        if (outStackVec == inStackVec) return true;
        return false;
    }
};

// 快慢指针
class Solution2 {
public:
    bool isPalindrome(ListNode* head) {
        // 首先设置快慢指针
        ListNode *fast = head, *slow = head;
        while (fast->next != nullptr) {
            fast = fast->next;
            if (fast->next != nullptr) {
                fast = fast->next;
            }else {
                break;
            }
            slow = slow->next;
        }
        // 以后面的slow指针为起点，翻转链表
        ListNode *curr = slow->next, *pre = nullptr;
        while (curr != nullptr) {
            ListNode* nextNode = curr->next;
            curr->next = pre;
            pre = curr;
            curr = nextNode;
        }
        // 反转后现在的pre是反转后链表的首节点
        ListNode *leftHead = head, *p = pre;
        while (p != nullptr) {
            if (p != leftHead) return false;
            p = p->next;
            leftHead = leftHead->next;
        }
        return true;
    }
};

int main() {
    return 0;
}
