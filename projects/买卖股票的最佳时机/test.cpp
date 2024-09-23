#include<vector>

using namespace std;

// 看某个数右边的最大的数是多少，然后进行比较
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxPro = 0;
        vector<int> rightMax = vector<int>(prices.size(), 0);
        rightMax[prices.size()-1] = prices[prices.size()-1];
        for (int i = prices.size()-2; i >= 0; i--) {
            rightMax[i] = prices[i] >= rightMax[i+1] ? prices[i] : rightMax[i+1];
            maxPro = max(maxPro, rightMax[i] - prices[i]);
        }
        return maxPro;
    }
};

int main() {
    return 0;
}