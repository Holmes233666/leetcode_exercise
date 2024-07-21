#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

// 基本思路：双指针，后移的右指针找到第一个高于左指针；在这过程中记录需要减去的面积的和
class Solution {
public:
    int trap(vector<int>& height) {
        int tot = 0;
        int start = 0; 
        // 跳过最开始的非降序情况
        while(start < height.size() - 1 && height[start+1] >= height[start]) {
            start++;
        }
        // 从第一个降序开始尝试接雨水
        for (int left = start; left < height.size() - 1; ) {
            // 对于紧密的右侧低于left的情况是可以构成盛水的容器的，那么不断右移right指针，直到找到第一个高于等于左指针的height
            int right = left + 2;
            int minus_squ = height[left+1];
            int notfindhigh_squ = minus_squ;
            int maxHeightIndex = left + 1;
            vector<int> vec;
            // 寻找右指针位置
            while (right < height.size() && height[right] < height[left]) {
                minus_squ += height[right];
                // 为找不到比left更高的柱子做准备：记录中间过程中最高的柱子
                maxHeightIndex = height[maxHeightIndex] > height[right] ? maxHeightIndex : right;
                right++;
            }

            // 成功接到雨水：找到更高的
            if (right < height.size() && height[right] >= height[left]) {
                tot += (right - left - 1) * height[left] - minus_squ;
                // 移动指针位置
                while(right < height.size() - 1 && height[right+1] > height[right]) {
                    right++;
                }
                left = right;
                continue;
            }
            // 成功接到雨水：找到最后一个都没找到更高的，那么期间最高的一个就作为一个承接点
            if (right == height.size() && right - left > 1) {
                int minus = 0;
                for (int k = left+1; k < maxHeightIndex; k++) {
                    minus += height[k];
                }
                tot += height[maxHeightIndex] * (maxHeightIndex - left - 1) - minus;
                left = maxHeightIndex;
                continue;
            }
            // 接不到雨水
            left++;
        }
        return tot;
    }
};

// 力扣：直觉解法；超时
class Solution1 {
public:
    int trap(vector<int>& height) {
        int tot = 0;
        for (int start = 1 ; start < height.size(); start++) {
            int max_left = 0, max_right = height.size() - 1;
            int max_left_num = height[max_left], max_right_num = height[max_right];
            while (max_left <= start) {
                max_left_num = max(height[max_left], max_left_num);
                max_left++;
            }
            while (max_right >= start) {
                max_right_num = max(height[max_right], max_right_num);
                max_right--;
            }
            // 求当前start的水量
            // cout << "temp water:" << min(max_left_num, max_right_num) - height[start] <<endl;
            tot += min(max_left_num, max_right_num) - height[start];
        }
        return tot;
    }
};

// 力扣：基于Solution1进行优化，动态规划，提前知道每个点向左和向右的最高度柱子
class Solution2 {
public:
    int trap(vector<int>& height) {
        int tot = 0;
        vector<int> right_max_heights(height.size(), 0);
        right_max_heights[height.size()-1] =height[height.size()-1];
        // 从左向右看，看到的最大值；需要从右向左遍历
        for (int i = height.size()-2; i >= 0; i--) {
            right_max_heights[i] = max(right_max_heights[i+1], height[i]);
        }
        // 从右向左看，看到的最大值；需要从左向右遍历
        vector<int> left_max_heights(height.size(), 0);
        left_max_heights[0] = height[0];
        for (int i = 1; i < height.size(); i++) {
            left_max_heights[i] = max(left_max_heights[i-1], height[i]);
        }
        for (int start = 0 ; start < height.size(); start++) {
            tot += min(right_max_heights[start], left_max_heights[start]) - height[start];
        }
        return tot;
    }
};



// 最终方法
class Solution3 {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (height[left] < height[right]) {
                ans += leftMax - height[left];
                ++left;
            } else {
                ans += rightMax - height[right];
                --right;
            }
        }
        return ans;
    }
};


int main() {
    vector<int> height = {8,2,8,9,0,1,7,7,9};
    Solution2 solution;
    int res = solution.trap(height);
    cout << "the final res = " << res << endl;
    return 0;
}