#include <vector>
#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 定义四个方向
        vector<vector<int>> directions = {{0,1}, {1,0},{0,-1},{-1,0}};   // 右，下，左，上
        unordered_set<string> uset;
        int count = 0, term = 0, last_i = 0, last_j = 0;
        int totNum = matrix.size() * matrix[0].size();
        vector<int> res;
        while(count < totNum) {
            vector<int> currDire = directions[term % 4];
            while (last_i >= 0 && last_i < matrix.size() && last_j >= 0 && last_j < matrix[0].size() && !uset.count(to_string(last_i) + "," + to_string(last_j))) {
                uset.insert(to_string(last_i) + "," + to_string(last_j));
                count++;
                res.push_back(matrix[last_i][last_j]);
                last_i += currDire[0];
                last_j += currDire[1];
            }
            // 回退一步
            last_i -= currDire[0];
            last_j -= currDire[1];
            // 改变方向
            term++;
            // 更新方向
            last_i += directions[term % 4][0];
            last_j += directions[term % 4][1];
        }
        return res;
    }
};

class Solution2 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<vector<int>> dir = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        vector<int> res;
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<char>> visited(n, vector<char>(m, '0'));  // 初始标记为都没有访问过
        int num = n * m;
        int i = 0, j = 0;
        int k = 0;
        while (num--) {
            res.push_back(matrix[i][j]);
            visited[i][j] = '1';
            int nextI = i + dir[k % 4][0], nextJ = j + dir[k % 4][1];
            if (nextI < 0 || nextI >= n || nextJ < 0 || nextJ >= m || visited[nextI][nextJ] == '1') {    // 无效单元格
                k++;
                i += dir[k % 4][0];
                j += dir[k % 4][1];
            }else {
                i = nextI;
                j = nextJ;
            }
        }
        return res;
    }
};

// 法2： 尝试第二种做法
class Solution3 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int ub = 0, db = n-1, lb = 0, rb = m-1;
        vector<int> res;
        int currNum = 0;
        while (currNum < n * m) {
            for (int j = lb; j <= rb && currNum < n * m; j++) {
                res.push_back(matrix[ub][j]);
                currNum++;
            }
            ub++;
            for (int i = ub; i <= db && currNum < n * m; i++) {
                res.push_back(matrix[i][rb]);
                currNum++;
            }
            rb--;
            for (int j = rb; j >= lb && currNum < n * m; j--) {
                res.push_back(matrix[db][j]);
                currNum++;
            }
            db--;
            for (int i = db; i >= ub && currNum < n * m; i--) {
                res.push_back(matrix[i][lb]);
                currNum++;
            }
            lb++;
        }
        return res;
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