#include<queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct CompareListNode {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val; // 小顶堆
    }
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        priority_queue<ListNode*, std::vector<ListNode*>, CompareListNode> minHeap;
        ListNode *p = head;
        while (p != nullptr) {
            minHeap.emplace(p);
            p=p->next;
        }
        ListNode *newHead = new ListNode(0), *newTail = newHead;
        while (!minHeap.empty()) {
            ListNode* currMin = minHeap.top();
            minHeap.pop();
            newTail->next = currMin;
            newTail = currMin;
        }
        return newHead->next;
    }
};