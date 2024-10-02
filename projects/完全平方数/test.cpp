#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        vector<int> f = vector<int>(n+1,INT_MAX-1);
        f[0] = 1;
        for (int i = 2; i <= n; i++) {
            int SqrtI = int(sqrt(i));
            if (i == SqrtI * SqrtI) {
                f[i] = 1;
            }else{
                for (int j = 1; j <= SqrtI; j++) {
                    f[i] = min(f[i-j*j]+1, f[i]);
                }
            }
        }
        return f[n];
    }
};


