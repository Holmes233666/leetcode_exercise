#include<vector>
#include<stack>

using namespace std;

// 枚举宽度：超时
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        for (int left = 0; left < heights.size(); left++) {
            if (heights[left] == 0) continue;
            int miniHeight = heights[left];
            res = max(res, heights[left]);
            for (int right = left + 1; right < heights.size(); right++) {
                miniHeight = min(heights[right], miniHeight);
                res = max(miniHeight * (right - left + 1), res);
            }
        }
        return res;
    }
};

// 使用单调递增栈，遇到比栈顶小的元素持续进行弹栈，直到不比栈顶小，进行入栈
class Solution2 {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<pair<int, int>> numStack;
        numStack.push({heights[0],0});
        vector<int> rightFirLow = vector<int>(heights.size(), heights.size()-1);
        vector<int> leftFirLow = vector<int>(heights.size(), 0);
        int res = 0;
        // 先从右到左，求解每个位置的下一个最小值出现的位置
        for (int i = 1; i < heights.size(); i++) {
            while (!numStack.empty() && heights[i] < numStack.top().first) {
                rightFirLow[numStack.top().second] = i-1;
                numStack.pop();
            }
            numStack.push({heights[i], i});
        }

        stack<pair<int, int>> numStack2;
        numStack2.push({heights[heights.size()-1], heights.size()-1});
        // 然后从左到右，求解每个位置的下一个最小元素出现的位置
        for (int i = heights.size()-2; i >= 0; i--) {
            while (!numStack2.empty() && heights[i] < numStack2.top().first) {
                leftFirLow[numStack2.top().second] = i+1;
                numStack2.pop();
            }
            numStack2.push({heights[i], i});
        }
        // 求解完左边和右边的第一个比当前元素的下标（包括当前元素），然后对每个矩形求解其能构成的最大面积
        for (int i = 0; i < heights.size(); i++) {
            res = max(heights[i] * (rightFirLow[i] - leftFirLow[i] + 1), res);
        }
        return res;
    }
};

class Solution3 {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<pair<int, int>> numStack;
        numStack.push({heights[0],0});
        vector<int> rightFirLow = vector<int>(heights.size(), heights.size()-1);
        vector<int> leftFirLow = vector<int>(heights.size(), 0);
        int res = 0;
        // 先从右到左，求解每个位置的下一个最小值出现的位置
        for (int i = 1; i < heights.size(); i++) {
            while (!numStack.empty() && heights[i] < numStack.top().first) {
                rightFirLow[numStack.top().second] = i-1;
                numStack.pop();
            }
            leftFirLow[i] = numStack.top().second;
            numStack.push({heights[i], i});
        }
        // 求解完左边和右边的第一个比当前元素的下标（包括当前元素），然后对每个矩形求解其能构成的最大面积
        for (int i = 0; i < heights.size(); i++) {
            res = max(heights[i] * (rightFirLow[i] - leftFirLow[i] + 1), res);
        }
        return res;
    }
};

