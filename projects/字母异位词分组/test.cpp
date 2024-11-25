#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        // 先给字符排序，排序结果应该存储在另一个数组中，因此使用一个数组复制
        vector<string> ordered = strs;
        unordered_map<string, vector<string>> resMap;
        vector<vector<string>> resVec;
        for (int i = 0; i < n; i++) {
            sort(ordered[i].begin(), ordered[i].end());
        }
        // 依次遍历strs中的所有内容
        for (int i = 0; i < n; i++) {
            resMap[ordered[i]].push_back(strs[i]);
        }
        // 将hashmap中的所有结果放进resVec中返回
        for (auto it : resMap) {
            resVec.push_back(it.second);
        }
        return resVec;
    }
};

class Solution2 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        unordered_map<string, vector<string>> resMap;
        vector<vector<string>> resVec;
        // 先给所有的单词做字母统计，然后放入特定的value中
        for (int i = 0; i < n; i++) {
            vector<int> count(26, 0);
            for (int j = 0; j < strs[i].size(); j++) {
                count[strs[i][j]-'a']++;    // 统计词频
            }
            // 遍历统计结果，查找哈希表
            string key;
            for (int j = 0; j < 26; j++) {
                key.push_back(j + 'a');
                key.push_back(count[j] + '0');
            }
            resMap[key].push_back(strs[i]);
        }
        // 遍历哈希表，提取结果
        for (auto it : resMap) {
            resVec.push_back(it.second);
        }
        return resVec;
    }
};


int main() {
    unordered_set<string> myset = {"a", "b", "c"};
    unordered_set<string> myset2 = {"a", "b", "c"};
    if (myset == myset2) {
        cout << "equal" << endl;
    }else{
        cout << "not equal" << endl;
    }
    
    return 0;
}