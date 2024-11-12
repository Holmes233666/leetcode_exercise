#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;


// 使用队列记录每idx处的最小步数
class Solution {
public:
    int jump(vector<int>& nums) {
        unordered_map<int, int> umap;   // 索引-最小步数
        umap[0] = 0;
        for (int i = 1; i < nums.size(); i++) {
            umap[i] = INT_MAX;
        }
        queue<pair<int, int>> reachIndx;    // 索引-目前的步数
        reachIndx.emplace(0,0);
        while (!reachIndx.empty()) {
            // 弹栈，然后压栈可以进入的元素，并在umap中记录其最小步数
            int currIdx = reachIndx.front().first, currStep = reachIndx.front().second;
            reachIndx.pop();
            for (int i = 1; i <= nums[currIdx]; i++) {
                if (currIdx + i > nums.size()-1) break;
                if (umap[currIdx+i] > currStep + 1) {
                    umap[currIdx+i] = currStep + 1;
                    reachIndx.emplace(currIdx + i, currStep + 1);
                }
            }
        }
        return umap[nums.size()-1];
    }
};

// 方法2：动态规划：f(n): 到达索引位置n的最小步数；f(n) = f(n-x) +  1 , 其中 nums[n-x] >= x
class Solution2 {
public:
    int jump(vector<int>& nums) {
        vector<int> f = vector<int> (nums.size(), INT_MAX);
        f[0] = 0;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 1; j < i; j++) {
                if (nums[i-j] >= j) f[i] = min(f[i-j] + 1, f[i]);
            }
        }
        return f[nums.size()-1];
    }
};

// 方法3：贪心算法，每次选择跳的最远的点作为起点，其超过末尾的时刻就是最少的次数
class Solution3 {
public:
    int jump(vector<int>& nums) {
        int currIdx = 0, currMaxReach = 0;
        int currSteps = 0;
        while (currMaxReach < nums.size()-1) {
            int chooseIdx = 0, chooseSteps = -INT_MAX;
            // 找到currIdx对应的所有能到达的索引中最大的
            for (int i = 1; i <= nums[currIdx]; i++) {
                if (currIdx + i >= nums.size()) return currSteps+1;
                if (chooseSteps < nums[currIdx + i]) {
                    chooseIdx = currIdx + i;
                }
            }
            currIdx = chooseIdx;
            currSteps += 1;
        }
        return currSteps;
    }
};

// 在跳跃游戏的解法上进行优化，每次只要在超过maxStep时进行记录即可
class Solution4 {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int maxStep = 0, maxReach = 0, lastReach = 0;
        for (int i = 0; i < nums.size(); i++) {
            maxReach = max(maxReach, i + nums[i]);
            if (maxReach >= nums.size()-1) {
                return maxStep+1;
            }
            if (i == lastReach) {
                maxStep++;
                lastReach = maxReach;
            }
        }
        return maxStep;
    }
};


