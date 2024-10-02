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
