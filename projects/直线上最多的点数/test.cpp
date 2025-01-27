

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int maxNum = 0, n = points.size();
        if (n == 1 || n == 2) return n;
        for (int i = 0; i < n; i++) {
            int localMax = 0, infty = 0;
            unordered_map<double, int> umap;
            for (int j = i+1; j < n; j++) {
                double deltax = points[i][0] - points[j][0];
                double deltay = points[i][1] - points[j][1];
                if (deltax == 0) {
                    infty++;
                    localMax = max(localMax, infty);
                }else{
                    umap[deltay/deltax]++;
                    localMax = max(umap[deltay/deltax], localMax);
                }
            }
            maxNum = max(localMax, maxNum);
        }
        return maxNum+1;
    }
};
