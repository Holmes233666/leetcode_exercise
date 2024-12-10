#include<vector>

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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // leftNextNode和rightNextNode都指的是原来的左侧和右侧的结点
        ListNode *leftNode = head, *rightNextNode = nullptr, *leftNextNode = nullptr;
        // 首先找到left
        while (--left) {
            if (!left) leftNextNode = leftNode;
            leftNode = leftNode->next;
        }
        ListNode *pre = rightNextNode, *reverseTail = leftNode;  // 初始化，实际没找到这个结点
        int nodeNum = right - left + 1; // 需要反转的节点数量
        while(nodeNum--) {
            ListNode *next = leftNode->next;
            if (nodeNum) {  // 如果是最右边的结点了那么需要记录下这个节点
                rightNextNode = next;
            }
            leftNode->next = pre;
            pre = leftNode;
            leftNode = next;
        }
        reverseTail->next = rightNextNode;
        leftNode->next = leftNextNode;
        return head;
    }
};
