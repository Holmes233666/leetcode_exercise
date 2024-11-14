#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        vector<int> nums = {1, 5, 10, 50, 100, 500, 1000};
        unordered_map<int, char> umap = {
            {1000 , 'M'},
            {500, 'D'},
            {100, 'C'},
            {50, 'L'},
            {10, 'X'},
            {5, 'V'},

        };
    }
};
