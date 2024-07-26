#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int i = 0; i < matrix.size(); i++) {
            auto it = lower_bound(matrix[i].begin(), matrix[i].end(), target);
            if (it != matrix.end() && *it == target) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    return 0;
}