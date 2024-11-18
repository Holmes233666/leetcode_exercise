#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        vector<int> nums = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        unordered_map<int, char> umap = {
            {1000 , 'M'},
            {500, 'D'},
            {100, 'C'},
            {50, 'L'},
            {10, 'X'},
            {5, 'V'},
            {1, 'I'}
        };
        int suplus = num, currIdx = 0;
        string str = "";
        while (suplus != 0) {
            if (suplus - nums[currIdx] >= 0) {
                if (currIdx == 11) {
                    str.push_back('I');
                    str.push_back('V');
                }else if(currIdx == 9) {
                    str.push_back('I');
                    str.push_back('X');
                }else if(currIdx == 7) {    // 40
                    str.push_back('X');
                    str.push_back('L');
                }else if(currIdx == 5) {
                    str.push_back('X');
                    str.push_back('C');
                }else if(currIdx == 3) {
                    str.push_back('C');
                    str.push_back('D');
                }else if(currIdx == 1) {
                    str.push_back('C');
                    str.push_back('M');
                }else {
                    str.push_back(umap[nums[currIdx]]);
                }
                suplus -= nums[currIdx];
            }else {
                if (currIdx == 12) continue;
                currIdx++;
            }
        }
        return str;
    }
};
