
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


// 对链表进行原地处理
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode(0), *tail = head;
        // 从头尾指针开始做加法，中间进位用l表示：
        ListNode *p=l1, *q=l2;
        int l = 0;
        // 共同部分的增加；
        while (p!=nullptr && q!=nullptr) {
            int sum = p->val + q->val + l;
            ListNode *nextNode = new ListNode(sum % 10);
            l = sum / 10;
            tail->next = nextNode;
            tail = nextNode;
            p = p->next;
            q = q->next;
        }
        // 判断哪个链表进入了nullptr，取非null的链表的头
        ListNode *resNode = p==nullptr? q:p;
        while (resNode!=nullptr) {
            int sum = resNode->val + l;
            ListNode *nextNode = new ListNode(sum % 10);
            resNode = resNode->next;
            tail->next = nextNode;
            tail = nextNode;
            l = sum / 10;
        }
        if (l != 0) {
            ListNode *nextNode = new ListNode(l);
            tail->next = nextNode;
        }
        return head->next;
    }
};

// 更简短的写法：
class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode(0), *tail = head;
        // 从头尾指针开始做加法，中间进位用l表示：
        ListNode *p=l1, *q=l2;
        int l = 0;
        // 共同部分的增加；
        while (p!=nullptr || q!=nullptr) {
            int sum = 0;
            if (p!=nullptr) {
                sum += p->val;
                p = p->next;
            }
            if (q!=nullptr) {
                sum += q->val;
                q = q->next;
            }
            sum += l;
            ListNode *nextNode = new ListNode(sum % 10);
            l = sum / 10;
            tail->next = nextNode;
            tail = nextNode;
        }
        if (l != 0) {
            ListNode *nextNode = new ListNode(l);
            tail->next = nextNode;
        }
        return head->next;
    }
};