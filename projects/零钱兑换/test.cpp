#include<vector>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> f = vector<int>(amount+1, INT_MAX-1);
        f[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < coins.size(); j++) {
                if (coins[j] <= i) {
                    f[i] = min(f[i-coins[j]] + 1, f[i]);
                }
            }
        }
        if (f[amount] == INT_MAX-1) return -1;
        return f[amount];
    }
};

// 第二次刷
class Solution2 {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> f(amount+1, INT_MAX);
        // 初始化
        f[0] = 0;
        for (int i = 0; i < n; i++) {
            if (coins[i] <= amount) f[coins[i]] = 1;
        }
        for (int i = 0; i < amount; i++) {
            for (int j = 0; j < n; j++) {
                if(i-coins[j] >= 0 && f[i-coins[j]] != INT_MAX) f[i] = min(f[i], f[i-coins[j]] + 1);
            }
        }
        return f[amount] == INT_MAX ? -1 : f[amount];
    }
};