#include<vector>
#include<iostream>

using namespace std;

class Solution {
public:
    int getNum(int num) {
        if (num <= 2) return num;
        int x = 2;
        int count = 2;
        while (x < num) {
            x += x-1;
            count++;
        }
        return count;
    }
};

int main() {
    int n = 0, currNum = 0;
    Solution s;
    cin >> n;
    while (n--) {
        cin >> currNum;
        cout << s.getNum(currNum) << endl;
    }
}