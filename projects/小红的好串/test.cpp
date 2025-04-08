#include<iostream>
#include<unordered_map>
#include<string>

using namespace std;

class Solution {
public:

};


int main() {
    int n;
    string s;
    cin >> n;
    cin >> s;
    unordered_map<int, int> umap;
    long res = 0;
    for (int left = n-1; left >= 0; left--) {
        umap[s[left] - 'a'] = left; // 初始化最后出现的位置为当前位置
        for (int i = 0; i < n; i++) {
            
        }
    }
    return 0;
}
