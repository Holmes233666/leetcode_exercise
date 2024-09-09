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

class Solution2 {
    public:
        ListNode* swapPairs(ListNode* head) {
            if (head == nullptr || head->next == nullptr) return head;
            ListNode *currNode = head, *nextNode, *pre = new ListNode(), *res = currNode->next;
            // 如果是没有后续结点的单个节点就不用交换了， 因此终止条件设置为：
            while(currNode != nullptr && currNode->next != nullptr) {
                // 准备好下一个带交换的一组的头
                nextNode = currNode->next->next;
                // 本轮交换
                pre->next = currNode->next;
                currNode->next->next = currNode;
                pre = currNode;
                currNode = nextNode;
            }
            if (currNode == nullptr) {
                pre->next = nullptr;
            }else{
                pre->next = currNode;
            }
            return res;
        }
    };

int main () {
    vector<int> vec = {1,2,3,4};
    ListNode *head = new ListNode(), *tail = head;
    for (int i = 0; i < vec.size(); i++) {
        ListNode *newNode = new ListNode(vec[i]);
        tail->next = newNode;
        tail = newNode;
    }
    Solution2 s;
    s.swapPairs(head->next);
    return 0;
}