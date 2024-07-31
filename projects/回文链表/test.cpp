#include<iostream>
#include<stack>
#include<vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

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

int main() {
    return 0;
}
