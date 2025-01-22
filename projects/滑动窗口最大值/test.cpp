#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>
#include<deque>

using namespace std;

// 朴素想法
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        // 主要时间花费在找这个区间内的最大的元素是什么
        for (int left = 0, right = k - 1; right < nums.size(); right++, left++) {
            auto maxNum = max_element(nums.begin()+left, nums.begin()+right+1);
            res.push_back(*maxNum);
        }
        return res;
    }
};

// 大顶堆：关键在于不急于移出离开滑动窗口的元素，延迟移出，直到这个元素到堆顶，移除的时间复杂度由O(n)降低到O(1)
class Solution2 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> queue; 
        for (int i = 0; i < k; i++) {
            queue.emplace(nums[i], i);
        }
        vector<int> res;
        res.push_back(queue.top().first);
        for (int left = 1, right = k; left < nums.size(), right < nums.size(); left++, right++) {
            queue.emplace(nums[right], right);
            while (queue.top().second < left) {
                // 弹出堆顶元素
                queue.pop();
            }
            res.push_back(queue.top().first);
        }
        return res;
    }
};

// 单调队列
class Solution3 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> res;
        // 未形成完整的窗口
        for (int i = 0; i < k; i++) {
            // 是否可以直接将队列清空？
            while (!dq.empty() && nums[i] >= nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        res.push_back(nums[dq.front()]);
        // 已经形成完整的窗口
        for (int right = k; right < nums.size(); right++) {
            // 队尾元素小于窗口右侧新元素，那么队列清空
            while (!dq.empty() && nums[right] >= nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(right);
            // 如果队首的元素已经超过窗口，那么应该清除
            while (!dq.empty() && dq.front() <= right - k) {
                dq.pop_front();
            }
            // 队首元素是最大的元素
            res.push_back(nums[dq.front()]);
        }
        return res;
    }
};


// 第二次刷：双端队列，滑动窗口模板套用
class Solution4 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size(), maxNum = -INT_MAX;
        deque<pair<int, int>> dq; // 前一个int放数值，后一个int放idx
        vector<int> res;
        for (int left = 0, right = 0; right <= n; right++) {
            while(right - left + 1 > k) {
                res.push_back(dq.front().first);
                if (dq.front().second == left) {
                    dq.pop_front();
                }
                left++;
            }
            if (right == n) break;
            // 新元素的处理
            while (!dq.empty() && nums[right] > dq.back().first) {
                dq.pop_back();
            }
            dq.push_back({nums[right], right});
        }
        return res;
    }
};

int main() {
    return 0;
}