#include<vector>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = prerequisites.size();
        vector<int> res;
        vector<int> onpath(numCourses, 0);
        vector<int> visited(numCourses, 0);
        vector<vector<int>> matrix = vector<vector<int>> (numCourses, vector<int>());
        for (int i = 0; i < n; i++) {
            matrix[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }
        for (int i = 0; i < n; i++) {
            if (visited[prerequisites[i][0]] == 0) {    // 没有访问过
                onpath[prerequisites[i][0]] = 1;
                bool ifcircle = dfs(prerequisites[i][0], matrix, onpath, visited, res);
                res.push_back(prerequisites[i][0]);
                if (ifcircle) return {};
                onpath[prerequisites[i][0]] = 0;
            }
        }
        // 将所有没有在依赖关系中的结点加入数组
        for(int i = 0; i < numCourses; i++) {
            if (visited[i] == 0) {
                res.push_back(i);
            }
        }
        return res;
    }

    bool dfs(int currNode, vector<vector<int>>& matrix, vector<int>& onpath, vector<int>& visited, vector<int>& res) {
        visited[currNode] = 1;
        for (int i = 0; i < matrix[currNode].size(); i++) {
            int nextNode = matrix[currNode][i];
            if (onpath[nextNode] == 1) return true;    // 含有环
            if (visited[nextNode] == 0) {
                onpath[nextNode] = 1;
                bool ifonpath = dfs(nextNode, matrix, onpath, visited, res);
                if (ifonpath) return true;  // 含有环
                onpath[nextNode] = 0;
                res.push_back(nextNode);    // 如果已经访问过，那么不用深搜，也不用加入res数组。
            }
        }
        return false;   // 所有的深搜结果都没有环，返回false;
    }
};

