#include<iostream>
#include<unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 迭代写法
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *p = list1, *q = list2;
        ListNode *newHead = new ListNode(0), *newTail = newHead;
        while (p!=nullptr && q!= nullptr) {
            if (p->val <= q->val) {
                newTail->next = p;
                newTail = p;
                p = p->next;
            }else {
                newTail->next = q;
                newTail = q;
                q = q->next;
            }
        }
        ListNode *res = p==nullptr? q : p;
        while (res != nullptr) {
            newTail->next = res;
            newTail = res;
            res = res->next;
        }
        return newHead->next;
    }
};

// 递归写法
class Solution2 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) {
            return list2;
        }else if (list2 == nullptr) {
            return list1;
        }else if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }else {
            list2->next = mergeTwoLists(list2->next, list1);
            return list2;
        }
    }
};

int main() {
    return 0;
}