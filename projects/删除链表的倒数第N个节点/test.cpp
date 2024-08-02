#include<iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *newHead = new ListNode();
        newHead->next = head;
        ListNode *fast = newHead, *slow = newHead;
        int time = 0;
        // 快指针先走n步
        while (time < n) {
            fast = fast->next;
            time++;
        }
        while (fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        return newHead->next;
    }
};