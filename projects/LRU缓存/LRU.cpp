#include<unordered_map>
#include<iostream>

using namespace std;

struct LNode {
    int val;
    int key;
    LNode *next;
    LNode *pre;
    LNode() : val(0), next(nullptr), pre(nullptr) {}
    LNode(int x, int key) : val(x), key(key), next(nullptr), pre(nullptr) {}
    LNode(int x, int key, LNode *next) : val(x), key(key), next(next), pre(nullptr) {}
    LNode(int x, int key, LNode *next, LNode *pre) : val(x), key(key), next(next), pre(pre) {}

};

class LRUCache {
public:
    int cap;
    LNode *head = new LNode(), *tail = head;
    std::unordered_map<int, LNode*> umap;  // key是插入的key值，value是该key的指针
    LRUCache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        if (umap.count(key)) {
            cout << umap.size() << endl;
            LNode *node = umap[key];
            // 将该结点放置链表表尾，视作最新访问的
            // 本身就是链表尾部
            if (node->next == nullptr) {
                return node->val;
            }
            // 本身在链表中间，前面有head，后面还有一个结点
            node->pre->next = node->next;
            node->next->pre = node->pre;
            tail->next = node;
            node->next = nullptr;
            node->pre = tail;
            tail = node;
            return node->val;
        }else {
            return -1;
        }
    }

    void put(int key, int value) {
        // put应该先查询有没有该健
        LNode *node;
        // 有的话修改该健：
        if (umap.count(key)) {
            node = umap[key];
            // 先修改
            node->val = value;
            // 不只有一个结点 （只有一个结点那么什么都不用做了）
            if (node->next != nullptr){
                // 再移动到队尾
                node->pre->next = node->next;
                node->next->pre = node->pre;
                tail->next = node;
                node->pre = tail;
                node->next = nullptr;
                tail = node;
            }
        }else {// 没有的话需要插入
            // 首先判断是否缓存满
            // 缓存满
            if (umap.size() == cap) {
                // 先删除head开头的健
                LNode *deleteNode = head->next;
                // 不只有一个结点
                if (deleteNode->next != nullptr) {
                    head->next = deleteNode->next;
                    deleteNode->next->pre = head;
                }else{// 只有一个结点
                    tail = head;
                }
                umap.erase(deleteNode->key);
                delete(deleteNode);
            }// 缓存不满/缓存满了但已经删除了满的健
            // 插入新的键：
            node = new LNode(value, key);
            cout << "curr key - value is " << key << " " << value << endl;
            tail->next = node;
            node->pre = tail;
            tail = node;
            umap[key] = node;
        }
    }
};