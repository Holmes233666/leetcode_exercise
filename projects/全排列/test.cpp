#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> visited = vector<bool> (nums.size(), false);
        for (int i = 0; i < nums.size(); i++) {
            // 求解以每个数字为首的全排列
            vector<int> resi;
            DFS(nums, resi, visited);
        }
        return res;
    }

    // 每次遍历不在栈中的元素，栈使用一个哈希表维护
    void DFS(vector<int>& nums, vector<int>& resi, vector<bool>& visited) {
        // 形成全排列
        if (resi.size() == nums.size()) {
            res.push_back(resi);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i] == false) {
                visited[i] = true;
                resi.push_back(nums[i]);
                DFS(nums, resi, visited);
                resi.pop_back();
                visited[i] = false;
            }
        }
    }
};
