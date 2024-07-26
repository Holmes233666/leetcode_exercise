#include <vector>
#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        reverse(matrix.begin(), matrix.end());
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i ; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<int> result = sol.spiralOrder(matrix);
    for (int num : result) {
        cout << num << " ";
    }
    return 0;
}