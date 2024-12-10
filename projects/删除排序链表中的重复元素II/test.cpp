#include<vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;
        // 使用pre，current和next指针
        ListNode *pre = new ListNode(0, head), *current = head;
        ListNode *res = pre;
        while (current != nullptr) {
            if (current->next != nullptr && current->val == current->next->val) {
                int currentVal = current->val;
                while (current != nullptr && current->val == currentVal) {
                    current = current->next;
                }
            }else {
                pre->next = current;
                pre = current;
                current = current->next;
            }
        }
        pre->next = current;
        return res->next;
    }
};
