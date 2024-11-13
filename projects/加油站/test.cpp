#include<vector>

using namespace std;

// 错误解法：最大子数组
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size(), maxStart = 0, maxCulDiff = 0, lastStart = 0, lastCulDiff = 0;
        // 首先计算差值，然后对根据差值计算由负数差值间断的子数组的和，找出最大的和
        vector<int> diff(n, 0);
        for (int i = 0; i < n; i++) {
            diff[i] = gas[i] - cost[i];
            if (diff[i] < 0) {
                if (maxCulDiff < lastCulDiff) {
                    maxStart = lastStart;
                    maxCulDiff = lastCulDiff;
                }
            }else {
                if (i >= 1 && diff[i-1] < 0) {
                    lastStart = i;
                    lastCulDiff = 0;
                }
                lastCulDiff += diff[i];
                if (i == n-1 && maxCulDiff < lastCulDiff) {
                    maxStart = lastStart;
                }
            }
        }
        int currDiff = 0;
        // 根据maxStart往后计算是否总和为正数
        for (int i = maxStart; i < maxStart + n; i++) {
            currDiff += diff[i % n];
            if (currDiff < 0) return -1;
        }
        return maxStart;
    }
};

// 正确解法：贪心：
class Solution2 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        // 首先构造一个环
        for(int i = 0; i < n-1; i++) {
            gas.push_back(gas[i]);
            cost.push_back(cost[i]);
        }
        // 然后对于每个点，尝试走n步
        for(int i = 0; i < n; ) {
            int totDiff = 0, j = i;
            while (totDiff >= 0 && j - i <= n - 1) {
                int currDiff = gas[j] - cost[j];
                totDiff += currDiff;
                j++;
            }
            if (totDiff >= 0 && j - i == n - 1) {
                return i;
            }
            // 否则累计的diff小于0（不能到达）
            i = j;
        }
        return -1;
    }
};
