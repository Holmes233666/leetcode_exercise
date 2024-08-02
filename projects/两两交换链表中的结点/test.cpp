struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *pre = new ListNode();
        ListNode *res = head->next;
        ListNode *p = head, *q = head->next;
        while (p!=nullptr && q!= nullptr) {
            p->next = q->next;
            pre->next = q;
            q->next = p;
            pre = p;
            p = p->next;
            q = q->next;
        }
        return res;
    }
};