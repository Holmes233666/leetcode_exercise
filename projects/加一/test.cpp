#include <vector>

using namespace std;

class Solution {
public:
    std::vector<int> plusOne(vector<int>& digits) {
        vector<int> res;
        int n = digits.size(), left = 0;
        for (int i = n-1; i >= 0; i--) {
            int nextNum;
            if (i == n-1) {
                nextNum = (digits[n-1] + 1) % 10;
                left = (digits[n-1] + 1) / 10;
            }else {
                nextNum = (digits[i] + left) % 10;
                left = (digits[i] + left) / 10;
            }
            res.push_back(nextNum);
        }
        if (left != 0) res.push_back(left);
        reverse(res.begin(), res.end());
        return res;
    }
};
