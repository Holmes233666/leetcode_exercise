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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || k == 0) return head;
        // 首先扫描一遍，记录链表长度
        ListNode *p = head;
        int len = 0;
        while (p != nullptr) {
            len++;
            p = p->next;
        }
        // 使用快慢指针，倒数第k+1个结点，以及找到倒数第k个结点
        int term = k % len + 1;
        ListNode *fast = head, *slow = head, *tail = head;
        while (fast!= nullptr && term--) {
            if (fast->next == nullptr) tail = fast;
            fast = fast->next;
        }
        // 然后两个指针一起走
        while (fast != nullptr) {
            if (fast->next == nullptr) tail = fast;
            fast = fast->next;
            slow = slow->next;
        }
        // 此时slow指向倒数第k+1个结点。
        ListNode *newHead = slow->next;
        if (!newHead) return head;
        slow->next = nullptr;
        tail->next = head;
        return newHead;
    }
};