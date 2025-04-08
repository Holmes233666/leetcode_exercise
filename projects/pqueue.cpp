#include<iostream>
#include<vector>
#include <stdexcept> // 用于抛出异常

using namespace std;

class MyQueue {
public:
    vector<int> nums;

    // 上浮操作：新插入元素，直接放到数组末尾，然后向上走
    void up(int idx) {
        int parent_idx = (idx - 1) / 2;
        while (idx > 0 && nums[parent_idx] < nums[idx]) {
            swap(nums[parent_idx], nums[idx]);
            idx = parent_idx;
            parent_idx = (idx - 1) / 2;
        }
    }

    // 下沉操作：顶部元素向下移动
    void down(int idx) {
        int n = nums.size();
        while (idx < n) {
            int left_child = idx * 2 + 1, right_child = idx * 2 + 2;
            int largest = idx;
            if (left_child < n && nums[largest] < nums[left_child]) {
                largest = left_child;
            }
            if (right_child < n && nums[largest] < nums[right_child]){
                largest = right_child;
            }
            if (largest == idx) {
                break;
            }
            swap(nums[largest], nums[idx]);
            idx = largest;
        }
    }

    void push(int num) {
        nums.push_back(num);
        int n = nums.size();
        up(n-1);
    }

    int pop() {
        int n = nums.size();
        if (n != 0) {
            int res = nums[0];
            swap(nums[0], nums[n-1]);
            nums.pop_back();
            // 下沉
            down(0);
            // 返回
            return res;
        }
        throw out_of_range("Heap is empty");
    }

};

int main() {
    MyQueue my_queue;
    vector<int> nums = {2,5,8,1,9,5,4};
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        my_queue.push(nums[i]);
    }
    // 依次取出堆中的元素
    for (int i = 0; i < n; i++) {
        cout << my_queue.pop() << " ";
    }
    return 0;
}