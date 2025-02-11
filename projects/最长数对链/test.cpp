#include<vector>

using namespace std;

// 贪心做法：O(nlogn)
class Solution {
public:
    static bool cmp(vector<int>& p1, vector<int>& p2) {
        return p1[1] < p2[1];   // 升序排列：小于号
    }
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), cmp);
        int curr = INT_MIN, res = 0;
        for (auto p : pairs) {
            if (curr < p[0]) {
                curr = p[1];
                res++;
            }
        }
        return res;
    }
};

// dp做法：O(n^2)
class Solution2 {
public:
    static bool cmp(vector<int>& p1, vector<int>& p2) {
        return p1[1] < p2[1];
    }
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size(), res = 1;
        sort(pairs.begin(), pairs.end(), cmp);
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++) {
            int currLeft = pairs[i][0];
            for (int j = i - 1; j >= 0; j--) {
                if (currLeft > pairs[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(dp[i], res);
        }
        return res;
    }
};