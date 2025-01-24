#include<vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int k = 2 + 1;
        vector<vector<int>> buy(n, vector<int>(k, -prices[0])), sell(n, vector<int>(k, 0));
        for (int i = 1; i < n; i++) {
            buy[i][1] = max(buy[i-1][1], -prices[i]);
            buy[i][2] = max(buy[i-1][2], sell[i-1][1] - prices[i]);
            sell[i][1] = max(buy[i-1][1] + prices[i], sell[i-1][1]);
            sell[i][2] = max(buy[i-1][2] + prices[i], sell[i-1][2]);
        }
        return sell[n-1][2];
    }
};

// 滚动数组优化
class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int k = 2 + 1;
        vector<int> buy(k, -prices[0]), sell(k, 0);
        for (int i = 1; i < n; i++) {
            buy[1] = max(buy[1], -prices[i]);
            buy[2] = max(buy[2], sell[1] - prices[i]);
            sell[1] = max(buy[1] + prices[i], sell[1]);
            sell[2] = max(buy[2] + prices[i], sell[2]);
        }
        return sell[2];
    }
};
