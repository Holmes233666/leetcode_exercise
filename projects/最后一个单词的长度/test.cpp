#include<vector>
#include<sstream>
#include<iostream>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        vector<string> strings;
        stringstream ss(s);
        string word;
        while (ss >> word) {
            strings.push_back(word);
        }
        // 找到最后一个string，并检查长度
        return strings[strings.size()-1].size();
    }
};