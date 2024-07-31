#include<iostream>
#include<unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 使用哈希表
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* p;
        unordered_set<ListNode*> umap;
        while (p != nullptr) {
            if (!umap.count(p)) {
                umap.insert(p);
                p = p->next;
            }else {
                return true;
            }
        }
        return false;
    }
};

int main() {
    return 0;
}
