#include<vector>
#include<queue>
#include<iostream>
#include <__filesystem/directory_entry.h>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int currLastOrange = 0, preLastOrange = 1, t = 0;
        // 记录一共有多少个橘子
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) currLastOrange++;
            }
        }
        // 访问记录数组，防止本轮被传染的句子传染别的橘子
        vector<vector<int>> visted = vector<vector<int>>(grid.size(), vector<int>(grid[0].size(),0));

        preLastOrange = currLastOrange + 1;
        while((preLastOrange != currLastOrange)) {
            if (currLastOrange == 0) break;
            preLastOrange = currLastOrange;
            for (int i = 0; i < grid.size(); i++) {
                for (int j = 0; j < grid[i].size(); j++) {
                    // 是个坏橘子，且没被访问过
                    if (grid[i][j] == 2 && visted[i][j] == 0) {
                        currLastOrange = searchFourDir(grid, visted, i, j, currLastOrange);
                    }
                }
            }
            // 重置visted;
            visted = vector<vector<int>>(grid.size(), vector<int>(grid[0].size(),0));
            t++;
        }
        if (currLastOrange != 0) return -1;
        return t;
    }

    int searchFourDir(vector<vector<int>>& grid, vector<vector<int>>& visted, int currI, int currJ, int currLastOrange) {
        visted[currI][currJ] = 1;
        vector<vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        for (int i = 0; i < directions.size(); i++) {
            int nextI = currI + directions[i][0], nextJ = currJ + directions[i][1];
            if (nextI >= 0 && nextJ >= 0 && nextI < grid.size() && nextJ < grid[0].size() && grid[nextI][nextJ] == 1) {
                currLastOrange--;
                grid[nextI][nextJ] = 2;
                visted[nextI][nextJ] = 1;
            }
        }
        return currLastOrange;
    }
};

class Solution2 {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int currLastOrange = 0, preLastOrange = 1, t = 0;
        queue<pair<int, int>> q;
        vector<vector<int>> times = vector<vector<int>>(grid.size(), vector<int>(grid[0].size(), INT_MAX));
        vector<vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        // 记录一共有多少个好橘子，将坏橘子放进队列中
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) currLastOrange++;
                if (grid[i][j] == 2) {
                    q.emplace(i,j);
                    times[i][j] = 0;
                }
            }
        }
        // 进行广度优先搜索
        while (!q.empty() && currLastOrange > 0) {
            auto [currI, currJ] = q.front();
            if (times[currI][currJ] != t) t++;
            for (int i = 0; i < directions.size(); i++) {
                int nextI = currI + directions[i][0], nextJ = currJ + directions[i][1];
                if (nextI < grid.size() && nextI >=0 && nextJ < grid[0].size() && nextJ >= 0 && grid[nextI][nextJ] == 1) {
                    q.emplace(nextI, nextJ);
                    grid[nextI][nextJ] = 2;
                    times[nextI][nextJ] = t+1;
                    currLastOrange--;
                }
            }
            q.pop();
        }
        if (currLastOrange != 0) return -1;
        return t;
    }
};

int main() {
    vector<vector<int>> res = {{2,1,1},{1,1,0},{0,1,1}};
    Solution2 s;
    cout << "Final Result is" <<s.orangesRotting(res) << endl;
}

