struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *p = head, *newHead = new ListNode(), *p1 = newHead, *p2 = newHead;
        while (p != nullptr) {
            if (p->val < x) {
                ListNode *nextNode = p1->next;
                p1->next = new ListNode(p->val, nextNode);
                p1 = p1->next;
            }else {
                if (p1->next == nullptr) {
                    p2 = p1;
                }
                ListNode *nextNode = p2->next;
                p2->next = new ListNode(p->val, nextNode);
                p2 = p2->next;
            }
            p = p->next;
        }
        return newHead->next;
    }
};