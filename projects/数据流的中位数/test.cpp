#include<queue>

using namespace std;

class MedianFinder {
public:
    // 在总数为偶数时，中位数为两个堆堆顶元素的平均数
    // 当总数为奇数时，中位数为
    priority_queue<int, vector<int>, greater<int>> Sq;  // 小顶堆， 存储大于中位数的那一半
    priority_queue<int, vector<int>, less<int>> Bq;     // 大顶堆， 存储小于等于中位数的那一半

    MedianFinder() {

    }

    void addNum(int num) {
        if (Bq.size() == Sq.size()) {  // 当放之前总数为偶数时，将该数放入小顶堆中
            Sq.push(num);
            Bq.push(Sq.top());
            Sq.pop();
        }else { // 当总数为奇数时，将该数放入大顶堆中
            Bq.push(num);
            Sq.push(Bq.top());
            Bq.pop();
        }
    }

    double findMedian() {
        if ((Sq.size() + Bq.size()) % 2 == 0) {
            return (Sq.top() + Bq.top()) / 2.0;
        }
        return Bq.top();
    }
};