#include<vector>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size(), number = n;
        vector<int> res(n, 1);
        // 从左向右扫描，保证如果right比left大，那么一定有res[right] > res[left]
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i-1] && res[i] <= res[i-1]) {
                number++;
                res[i]++;
            }
        }
        // 从右向左扫描，保证如果left比right大，那么一定有res[left] > res[right]
        for (int i = n-2; i >= 0; i--) {
            if (ratings[i] > ratings[i+1] && res[i] >= res[i+1]) {
                number++;
                res[i]++;
            }
        }
        return number;
    }
};