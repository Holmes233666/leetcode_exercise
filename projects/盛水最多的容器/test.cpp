#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size()-1;
        int water = 0;
        //cout << "height[right]=" << height[right] << " height[left]=" << height[left] << endl;
        while(right > left && left < height.size() && right >= 0) {
            // 计算当前的水
            //cout << left << " " << right << endl;
            //cout << "height[right]=" << height[right] << " height[left]=" << height[left] << endl;
            water = max(min(height[right], height[left]) * (right - left), water);
            // 右边的高度大于左边的，那么右移左边的
            if (height[right] >= height[left]) {
                left++;
            }else{
                right--;
            }
        }
        return water;
    }
};

int main() {
    Solution solution;
    vector<int> vec = {1,8,6,2,5,4,8,3,7};
    solution.maxArea(vec);
    return 0;
}