#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int startI = 0, startJ = matrix[0].size();
        while (startI <= matrix.size()-1 && startJ >=0) {
            if (matrix[startI][startJ] == target) return true;
            if (matrix[startI][startJ] > target) {
                startJ--;
                continue;
            }
            startI++;
        }
        return false;
    }
};

class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // 首先对列进行二分查找
        vector<int> col;
        for (int i = 0; i < matrix.size(); i++) {
            col.push_back(matrix[i][0]);
        }
        int rowIdx = binarySearch(target, 0, col.size()-1, col);
        if (rowIdx < 0 || rowIdx >= matrix.size()) return false;
        // 对第colIdx行进行检索
        int colIndex = binarySearch(target, 0, matrix[rowIdx].size()-1, matrix[rowIdx]);
        if (colIndex < 0) return false;
        if (matrix[rowIdx][colIndex] == target) return true;
        return false;
    }
    int binarySearch(int target, int start, int end, vector<int>& nums) {
        if (start == end) {
            if (nums[start] <= target) return start;
            if (nums[start] > target) return start-1;
        }

        int mid = (start + end) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target) return binarySearch(target, start, mid, nums);
        return binarySearch(target, mid+1, end, nums);

    }
};

int main() {

}