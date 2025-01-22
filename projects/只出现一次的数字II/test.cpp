#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        unordered_map<int, int> umap;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            umap[nums[i]]++;
            if (umap[nums[i]] == 3) umap.erase(nums[i]);
        }
        auto it = umap.begin();
        return it->first;
    }
};

// 法2： 利用取余关系
class Solution2 {
public:
    int singleNumber(std::vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        for (int j = 0; j < 32; j++) {
            int tot = 0;
            for (int i = 0; i < n; i++) {
                // 取出第j位的数
                tot += (nums[i] >> j) & 1;
            }
            res |= tot % 3 == 0 ? (0 << j) : (1 << j);
        }
        return res;
    }
};
