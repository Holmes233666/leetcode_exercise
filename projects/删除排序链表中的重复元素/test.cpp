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
        // 使用pre指针和current指针
        if (head == nullptr) return head;
        for (ListNode *current = head->next, *pre = head; current != nullptr; ) {
            if (current->val != pre->val) {
                pre = current;
                current = current->next;
            }else { // 如果current指针在和pre相同，那么current一直前进，直到二者不相同或者curr = nullptr
                while (current != nullptr && current->val == pre->val) {
                    current = current->next;
                }
                pre->next = current;
                pre = current;
                if (current == nullptr) break;
                current = current->next;
            }
        }
        return head;
    }
};