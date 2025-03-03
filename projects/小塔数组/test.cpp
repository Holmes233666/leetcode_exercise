#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int goodNum(vector<int>& vec) {
        int cnt = 0;
        int n = vec.size();
        for (int i = 0; i < n; i++) {
            if (ifGood(vec[i])) cnt++;
        }
        return cnt;
    }

    bool ifGood(int num) {
        bool hasOdd = false;  // Changed to bool
        int sum = 0;
        while (num != 0) {
            int lastNum = num % 10;
            if (lastNum % 2 != 0) {
                hasOdd = true;
            }
            sum += lastNum;
            num = num / 10;
        }
        return hasOdd && (sum % 2 == 0);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    Solution s;
    cout << s.goodNum(nums) << endl;
    return 0;
}
