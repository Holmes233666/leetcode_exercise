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
        unordered_map<string, vector<string>> hash_map;
        vector<vector<string>> result;
        for (int i=0; i<strs.size(); i++) {
            string temp = strs[i];
            sort(temp.begin(), temp.end());
            hash_map[temp].push_back(strs[i]);
        }
        // 提取hash_map中所有的values
        for (const auto& pair :hash_map) {
            result.push_back(pair.second);
        }
        return {};
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