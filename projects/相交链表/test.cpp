#include<iostream>
#include<unordered_map>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

// 方法1： 计算链表的长度，较长的链表先走|a-b|
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // 若其中一个为空，直接返回null
        if (headA == nullptr or headB == nullptr) return nullptr;

        //首先记录两个链表的长度
        int lenA = 1, lenB = 1;
        ListNode* p = headA;
        ListNode* q = headB;
        ListNode *p2, *q2;

        p2 = p, q2 = q;

        while (p2->next != nullptr) {
            lenA++;
            p2 = p2->next;
        }

        while (q2->next != nullptr) {
            lenB++;
            q2=q2->next;
        }

        // 长度较长的链表先走几步
        while (lenA > lenB) {
            p = p->next;
            lenA--;
        }
        while (lenB > lenA) {
            q = q->next;
            lenB--;
        }

        // 两个链表一起走，直到遇到相同的结点
        while (p != nullptr && q != nullptr && q != p ) {
            q = q->next;
            p = p->next;
        }

        if (p != nullptr && q != nullptr) return q;
        return nullptr;
    }
};

// 方法2： 双指针，每个指针走|a+b|，走的长度是相同的
class Solution2 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA, *q = headB;
        while (p != q) {
            if (p==nullptr) p = headB;
            if (q==nullptr) q = headA;
            p = p->next;
            q = q->next;
        }
        return p;
    }
};

// 方法3： 哈希表
class Solution3 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA, *q = headB;
        unordered_map<ListNode*, int> umap;
        while (p!=nullptr) {
            umap[p]++;
            p = p->next;
        }
        while (q!=nullptr) {
            if (umap.count(q)) return q;
            q = q->next;
        }
        return nullptr;
    }
};

int  main() {
    return 0;
}
