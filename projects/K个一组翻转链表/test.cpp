#include<iostream>
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
    // 返回尾结点和尾结点的下一个节点
    vector<ListNode*> reverseLinkNodeK(ListNode* head, ListNode* pre, int k) {
        vector<ListNode*> ListVec;
        ListNode *currNode = head, *nextNode;
        while(k--) {
            nextNode = currNode->next;
            currNode->next = pre;
            pre = currNode;
            currNode = nextNode;
        }
        ListVec.push_back(pre);
        ListVec.push_back(nextNode);
        return ListVec;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        int len = 0;
        ListNode *p = head, *res;
        // 首先记录链表的长度和要返回的头
        while (p!=nullptr) {
            len++;
            if (len == k) res = p;
            p=p->next;
        }
        // 一共要进行几轮旋转
        int term = len / k;
        // 初始化辅助指针pre
        ListNode *currHead = head, *pre = new ListNode();
        while (term--) {
            vector<ListNode*> vec = reverseLinkNodeK(currHead, pre, k);
            pre->next = vec[0];
            pre = currHead;
            currHead->next = vec[1];
            currHead = currHead->next;
        }
        return res;
    }
};


class Solution2 {
public:
    // 返回新的头结点和尾结点
    pair<ListNode*, ListNode*> reverseLinkNodeK(ListNode* head, ListNode* tail) {
        ListNode *pre = new ListNode(), *currNode = head, *tailNext = tail->next;
        pre->next = head;
        while(currNode != tailNext) {
            ListNode *nextNode = currNode->next;
            currNode->next = pre;
            pre = currNode;
            currNode = nextNode;
        }
        return {tail, head};
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *currTermHead = head, *currTermTail = head, *res = head;
        ListNode *preTail = new ListNode();
        for (int i = 0; ; i++) {
            int term = k;
            currTermTail = currTermHead;
            while(currTermTail != nullptr && --term) {
                currTermTail = currTermTail->next;
            }
            if (currTermTail == nullptr) {
                // 不足k个或者刚好就是完整的一组的末尾
                // 上一组的尾巴连上当前的头
                preTail->next = currTermHead;
                return res;
            }
            if (i == 0) res = currTermTail;
            // 保存下一个头
            ListNode *tempNode = currTermTail->next;
            // 根据currTermHead和currTermTail以及k反转链表
            auto [newHead, newTail] = reverseLinkNodeK(currTermHead, currTermTail);
            // 重新连接新的头到上一个链表的尾
            preTail->next = newHead;
            preTail = newTail;
            currTermHead = tempNode;
        }
    }
};

int main() {
    vector<int> vec = {1,2,3,4,5};
    int k = 2, num = 5, currNodeIndex = 0;
    ListNode *head = new ListNode(), *tail=head;
    while (currNodeIndex < num) {
        ListNode* tempNode = new ListNode(vec[currNodeIndex++]);
        tail->next = tempNode;
        tail = tail->next;
    }
    Solution s;
    s.reverseKGroup(head->next, k);
}