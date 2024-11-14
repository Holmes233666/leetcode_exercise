#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<string, int> umap;
    int romanToInt(string s) {
        int n = s.size(), currSum = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'I') {
                if (i + 1 < n && s[i+1] == 'V') {
                    currSum += 4;
                    i++;
                }else if (i + 1 < n &&  s[i+1] == 'X') {
                    currSum += 9;
                    i++;
                }else { // 就是1
                    currSum += 1;
                }
            }else if (s[i] == 'X') {
                if (i + 1 < n && s[i+1] == 'L') {
                    currSum += 40;
                    i++;
                }else if (i + 1 < n &&  s[i+1] == 'C') {
                    currSum += 90;
                    i++;
                }else { // 就是1
                    currSum += 10;
                }
            }else if (s[i] == 'V') {
                currSum += 5;
            }else if (s[i] == 'L') {
                currSum += 50;
            }else if (s[i] == 'C') {
                if (i + 1 < n && s[i+1] == 'D') {
                    currSum += 400;
                    i++;
                }else if (i + 1 < n &&  s[i+1] == 'M') {
                    currSum += 900;
                    i++;
                }else { // 就是100
                    currSum += 100;
                }
            }else if (s[i] == 'D') {
                currSum += 500;
            }else if (s[i] == 'M') {
                currSum += 1000;
            }
        }
        return currSum;
    }
};

class Solution2 {
public:
    unordered_map<char, int> umap;
    int romanToInt(string s) {
        umap['I'] = 1;
        umap['V'] = 5;
        umap['X'] = 10;
        umap['L'] = 50;
        umap['C'] = 100;
        umap['D'] = 500;
        umap['M'] = 1000;
        int n = s.size(), currSum = 0;
        for (int i = 0; i < n; i++) {
            int currNum = umap[s[i]];
            if (i < n - 1 && umap[s[i+1]] > currSum) {
                currSum -= currNum;
            }else {
                currSum += currNum;
            }
        }
        return currSum;
    }
};




