#include<vector>
#include<iostream>
#include<unordered_map>

using namespace std;


class Solution {
public:
    int getMaxVlue(vector<int>& tags, vector<int>& withTags, vector<int>& woutTags) {
        int n = tags.size();
        unordered_map<int, vector<int>> umap;
        for (int i = 0; i < n; i++) {
            umap[tags[i]].push_back(i);
        }
        int maxBu = 0;
        for (auto it : umap) {
            int tag = it.first;
            vector<int> temp = it.second;   // 序号列表
            // 找到对应序号如果分配的最大值，和如果没有分配的最小值；
            int maxGain = 0, maxLoss = 1000000, totLoss = 0;
            int maxGainIdx = -1, maxLossIdx = -1;
            for (int j = 0; j < temp.size(); j++) {
                // 找到 temp[j] 下标的获得值和损失值
                if (maxGain < withTags[temp[j]]) {
                    maxGain = withTags[temp[j]];
                    maxGainIdx = temp[j];
                }
                if (maxLoss > woutTags[temp[j]]) {
                    maxLoss = woutTags[temp[j]];
                    maxLossIdx = temp[j];
                }
                totLoss += woutTags[temp[j]];
            }
            if (maxGain > abs(maxLoss)) {    // 选择给收益最大的贴标签，其他的不贴
                maxBu += maxGain;
                // 其他的要减去
                maxBu += totLoss;
                maxBu -= woutTags[maxGainIdx];
            }else { // 给损失更大的贴标签
                maxBu += withTags[maxLossIdx];
                maxBu += totLoss;
                maxBu -= woutTags[maxLossIdx];
            }
        }
        return maxBu;
    }
};


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> tags, withTags, woutTags;
    for (int i = 0; i < n; i++) {
        cin >> tags[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> withTags[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> woutTags[i];
    }
    Solution s;
    s.getMaxVlue(tags, withTags, woutTags);
    return 0;
}