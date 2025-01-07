#include<string>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int n1 = a.size(), n2 = b.size();
        int i = n1-1, j = n2-1, plus = 0;
        while (i >= 0 && j >= 0) {
            int ac = a[i] - '0', bc = b[j] - '0';
            int resc = (ac + bc + plus) % 2;
            plus = (ac + bc + plus) / 2;
            res.push_back(resc + '0');
            i--;
            j--;
        }
        string left = i == -1 ? b : a;
        int k = i == -1 ? j : i;
        while (k >= 0) {
            int leftc = (left[k] + plus) % 2;
            plus = (left[k] + plus) / 2;
            res.push_back(leftc + '0');
            k--;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};