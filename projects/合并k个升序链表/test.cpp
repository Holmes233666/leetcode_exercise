#include<vector>
#include<algorithm>
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
    void mergeTwo(vector<ListNode*>& lists, int start, int mid, int end) {
        ListNode *p = lists[start], *q = lists[mid+1];
        ListNode *head = new ListNode(), *tail = head;
        tail->next = nullptr;
        while (p != nullptr && q != nullptr) {
            if (p->val <= q->val) {
                tail->next = p;
                p = p->next;
            }else {
                tail->next = q;
                q = q->next;
            }
            tail = tail->next;
        }
        tail->next = p == nullptr? q : p;
        lists[start] = head->next;
    }

    void mergeSort(vector<ListNode*>& lists, int start, int end) {
        if (start < end) {
            mergeSort(lists, start, (start + end) / 2);
            mergeSort(lists, (start + end) / 2 + 1, end);
            mergeTwo(lists, start, (start + end) / 2, end);
        }
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int start = 0, end = lists.size()-1;
        mergeSort(lists, start, end);
        return lists[0];
    }
};


int main() {
    vector<vector<int>> vec = {{}, {0,1}};
    vector<ListNode*> lists;
    for (int i = 0; i < vec.size(); i++) {
        ListNode *head = new ListNode(), *tail = head;
        for (int j = 0; j < vec[i].size(); j++) {
            ListNode *p = new ListNode(vec[i][j]);
            tail->next = p;
            tail = tail->next;
        }
        lists.push_back(head->next);
    }
    Solution s;
    ListNode* p = s.mergeKLists(lists);
    while(p != nullptr) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
    return 0;
}