#include<vector>
#include<queue>
#include<iostream>

using namespace std;

struct LinkNode {
    int val;
    LinkNode* next;
    LinkNode(int val): val(val), next(nullptr){}
    LinkNode(int val, LinkNode *next) : val(val),next(next) {}
};

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 初始化图
        vector<vector<int>> grid = createMatrix(prerequisites, numCourses);
        // 一开始所有的课程都没有被作为前驱过（被访问过）
        vector<vector<int>> visited = vector<vector<int>>(numCourses, vector<int>(numCourses, 0));
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (visited[i][j] == 0 && grid[i][j] == 1) {
                    // 进行深搜
                    bool ifCir = DFS(grid, visited, i, j);
                    if (ifCir == true) return false;    // 有环，返回false
                }
            }

        }
        return true;
    }

    vector<vector<int>> createMatrix(vector<vector<int>>& prerequisites, int numCourse) {
        vector<vector<int>> mat = vector<vector<int>> (numCourse, vector<int>(numCourse));
        for (int i = 0; i < prerequisites.size(); i++) {
            int sour = prerequisites[i][1], to = prerequisites[i][0];
            mat[sour][to] = 1;
        }
        return mat;
    }

    bool DFS(vector<vector<int>>& grid, vector<vector<int>>& visted, int sour, int to) {
        // 将当前结点标记为已经访问
        visted[sour][to] = 1;
        // 取出矩阵中to行对应的数据，进行深搜
        for (int i = 0; i < grid[to].size(); i++) {
            if (grid[to][i] == 0) continue;
            // 如果没访问过，且有边，那么进行深搜
            if (visted[to][i] == 0) {
                return DFS(grid, visted, to, i);
            }else if (visted[to][i] == 1) {
                // 有环
                return true;
            }
        }
        visted[sour][to] = 2;
    }
};

class Solution2 {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 初始化图
        vector<vector<int>> grid = createMatrix(prerequisites, numCourses);
        // 一开始所有的课程都没有被作为前驱过（被访问过）
        vector<vector<int>> visited = vector<vector<int>>(numCourses, vector<int>(numCourses, 0));
        vector<int> onpath = vector<int>(numCourses, 0);
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (visited[i][j] == 0 && grid[i][j] == 1) {
                    // 进行深搜
                    bool ifCir = DFS(grid, visited, onpath, i, j);
                    if (ifCir == true) return false;    // 有环，返回false
                }
            }

        }
        return true;
    }

    vector<vector<int>> createMatrix(vector<vector<int>>& prerequisites, int numCourse) {
        vector<vector<int>> mat = vector<vector<int>> (numCourse, vector<int>(numCourse));
        for (int i = 0; i < prerequisites.size(); i++) {
            int sour = prerequisites[i][1], to = prerequisites[i][0];
            mat[sour][to] = 1;
        }
        return mat;
    }

    bool DFS(vector<vector<int>>& grid, vector<vector<int>>& visted, vector<int>& onpath, int sour, int to) {
        // 将当前结点标记为已经访问
        visted[sour][to] = 1;
        // 取出矩阵中to行对应的数据，进行深搜
        for (int i = 0; i < grid[to].size(); i++) {
            if (grid[to][i] == 0) continue;
            // 如果没访问过，且有边，那么进行深搜
            if (visted[to][i] == 0) {
                onpath[to] = 1;
                return DFS(grid, visted, onpath, to, i);
            }else if (onpath[i] == 1) {
                // 有环
                return true;
            }
        }
        onpath[to] = 0;
    }
};

class Solution3 {
public:
    // 数组实现邻接表
    vector<vector<int>> grid;
    vector<int> visted;
    vector<int> onpath;
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        grid = vector<vector<int>> (numCourses, vector<int>());
        visted = vector<int> (numCourses, 0);
        onpath = vector<int> (numCourses, 0);
        bool flag = true;
        // 创建邻接表
        for (int i = 0; i < prerequisites.size(); i++) {
            int sour = prerequisites[i][1], to = prerequisites[i][0];
            grid[sour].push_back(to);
        }
        // 遍历所有的结点，进行深搜
        for (int i = 0; i < numCourses; i++) {
            if (visted[i] == 0) flag = DFS(i);
            if (flag) return (!flag);
        }
        return (!flag);
    }

    // 深度优先搜索
    bool DFS(int currNode) {
        onpath[currNode] = 1;
        visted[currNode] = 1;
        bool flag = false;  // 默认不含环
        for (int i = 0; i < grid[currNode].size(); i++) {
            int to = grid[currNode][i];
            if (onpath[to] == 1) {
                return true;    // 含有环
            }
            if (visted[to] == 1) {   // 访问过，不用继续深搜这个路线返回true
                continue;
            }else if (visted[to] == 0) {   // 没访问过，需要继续深搜
                flag = DFS(to);
                if (flag) break;
            }
        }
        onpath[currNode] = 0;
        return flag;
    }
};

int main() {

}