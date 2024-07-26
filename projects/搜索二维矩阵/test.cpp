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

class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int start_i = 0, start_j = matrix[0].size()-1;
        int currI = start_i, currJ = start_j;
        while (currI < matrix.size() && currJ >= 0) {
            int temp = matrix[currI][currJ];
            if (temp == target) return true;
            if (temp > target) {
                currJ--;
            }else {
                currI++;
            }
        }
        return false;
    }
};

int main() {
    return 0;
}