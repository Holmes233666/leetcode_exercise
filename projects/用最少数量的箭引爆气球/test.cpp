#include<vector>

using namespace std;

class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[0] < b[0]; // 升序排列
    }
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), cmp);
        int n = points.size(), shotNum = 0;
        for (int i = 0; i < n; ) {
            int currStart = i, nextStart = i + 1;
            while (nextStart < n && points[nextStart][0] >= points[currStart][1]) { // 直到找到一个不满足的区间
                nextStart++;
            }
            i = nextStart;
            shotNum++;
        }
        return shotNum;
    }
};