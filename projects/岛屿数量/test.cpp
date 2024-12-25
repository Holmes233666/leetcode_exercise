#include<vector>
#include<unordered_set>

using namespace std;

class Solution {
public:
    // 自定义pair<int, int>的哈希函数
    struct pair_hash {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2>& pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };

    unordered_set<pair<int, int>> uset;
    vector<vector<int>> direction = {{0,1},{1,0}, {0,-1}, {-1,0}};  // 右-下-左-上
    int numIslands(vector<vector<char>>& grid) {

        int res = 0;

        // 记录地图上所有的为1的网格的位置
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '1') uset.emplace(i,j);
            }
        }

        while (!uset.empty()) {
            auto it = uset.begin();
            pair<int, int> e = *it;
            int currI = e.first, currJ = e.second;

            DFS(grid, currI, currJ);
            res++;
        }
        return res;
    }

    void DFS(vector<vector<char>>& grid, int currI, int currJ) {
        // 将当前位置标记为已经搜索
        uset.erase({currI, currJ});
        for (int dirIndx = 0; dirIndx < direction.size(); dirIndx++) {
            int newI = currI + direction[dirIndx][0], newJ = currJ + direction[dirIndx][1];
            // 位置正确，且值是1，那么需要深搜。
            if (ifValidPos(grid, newI, newJ) && uset.find({newI, newJ}) != uset.end()) {
                DFS(grid, newI, newJ);
            }
        }

    }

    bool ifValidPos(vector<vector<char>>& grid, int i, int j) {
        if (i >= 0 && i <= grid.size() && j >= 0 && j <= grid[0].size()-1) return true;
        return false;
    }

};

// 原本使用unordered set无法直接实现对set的快速访问。
class Solution2 {
public:
    vector<vector<int>> direction = {{0,1},{1,0}, {0,-1}, {-1,0}};  // 右-下-左-上
    int numIslands(vector<vector<char>>& grid) {
        vector<vector<char>> visted = grid;
        int res = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '1') {
                    DFS(grid, visted, i, j);
                    res++;
                }
            }
        }
        return res;
    }

    void DFS(vector<vector<char>>& grid, vector<vector<char>>& visted, int currI, int currJ) {
        // 将当前位置标记为已经搜索
        visted[currI][currJ] = '0';
        for (int dirIndx = 0; dirIndx < direction.size(); dirIndx++) {
            int newI = currI + direction[dirIndx][0], newJ = currJ + direction[dirIndx][1];
            // 位置正确，且值是1，那么需要深搜。
            if (ifValidPos(grid, newI, newJ) && visted[newI][newJ] == '1') {
                DFS(grid, visted, newI, newJ);
            }
        }

    }
    bool ifValidPos(vector<vector<char>>& grid, int i, int j) {
        if (i >= 0 && i <= grid.size() && j >= 0 && j <= grid[0].size()-1) return true;
        return false;
    }

};


// 第二次刷：DFS + 数组标记
class Solution3 {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size(), res = 0;
        vector<vector<char>> visited(n, vector<char>(m, '0'));
        vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};  // 方向数组
        for (int start_i = 0; start_i < n; start_i++) {
            for (int start_j = 0; start_j < m; start_j++) {
                if (visited[start_i][start_j] == '0' && grid[start_i][start_j] == '1') {
                    DFS(grid, dir, visited, start_i, start_j, n, m);
                    res++;
                }
            }
        }
        return res;
    }

    void DFS(vector<vector<char>>& grid, vector<vector<int>>& dir, vector<vector<char>>& visited, int start_i, int start_j, int n, int m) {
        if (grid[start_i][start_j] == '1' && visited[start_i][start_j] == '0') {    // 没有访问过
            visited[start_i][start_j] = '1';
            for (int i = 0; i < 4; i++) {
                int new_i = start_i + dir[i][0], new_j = start_j + dir[i][1];
                if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < m
                    && grid[new_i][new_j] == '1' && visited[new_i][new_j] == '0') {
                    DFS(grid, dir, visited, new_i, new_j, n, m);
                    }
            }
        }
    }
};
