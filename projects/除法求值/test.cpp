#include<vector>
#include<list>
#include<unordered_map>

using namespace std;

class Graph {
public:
    int vertices; // 图的顶点数量
    unordered_map<string, int> ump;     // 由string映射到邻接表的数组下标
    vector<list<pair<string, double>>> adjList; // 邻接表，存储 <目标顶点, 权重>

    // 构造函数，初始化图
    Graph(int v, unordered_map<string, int>& umap) {
        vertices = v;
        adjList.resize(v);
        ump = umap;
    }

    // 添加带权边（有向图）
    void addEdge(string src, string dest, double weight) {
        adjList[ump[src]].emplace_back(dest, weight);
        adjList[ump[dest]].emplace_back(src, 1/weight);
    }
};

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int n = equations.size(), k = 0;
        unordered_map<string, int> umap;
        vector<double> resVec;
        // 建图，遍历得到顶点个数
        for (int i = 0; i < n; i++) {
            if (umap.find(equations[i][0]) == umap.end()) {
                umap[equations[i][0]] = k++;
            }
            if (umap.find(equations[i][1]) == umap.end()) {
                umap[equations[i][1]] = k++;
            }
        }
        vector<int> visited(k, 0);
        // k为顶点个数
        Graph g = Graph(k, umap);
        // 添加边
        for (int i = 0; i < n; i++) {
            g.addEdge(equations[i][0], equations[i][1], values[i]);
        }

        // 对每个查询进行深搜
        for (int i = 0; i < queries.size(); i++) {
            double res = -1.0;
            dfs(g, queries[i][0], queries[i][1], visited, 1, res);
            resVec.push_back(res);
            visited = vector<int>(k, 0);
        }
        return resVec;
    }

    void dfs(Graph& g, string& currNode, string& dest, vector<int>& visited, double val, double& res) {
        if (g.ump.find(currNode) == g.ump.end()) {
            return;
        }
        int idx = g.ump[currNode];
        list<pair<string, double>> l = g.adjList[idx];
        visited[idx] = 1;
        // 递归终止条件
        if (currNode == dest) {
            res = val;
            return;
        }
        for (auto it = l.begin(); it != l.end(); it++) {
            string nextNode = it->first;
            int nextIdx = g.ump[nextNode];
            if (visited[nextIdx] == 0) {    // 进行深搜
                dfs(g, nextNode, dest, visited, val*(it->second), res);
            }
        }
    }
};