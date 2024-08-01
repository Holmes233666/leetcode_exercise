#include<iostream>
#include<unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *p = head;
        unordered_map<ListNode*, int> umap;
        while (p!=nullptr) {
            if (umap.count(p)) return p;
            p = p->next;
        }
        return nullptr;
    }
};

int main() {
    return 0;
}