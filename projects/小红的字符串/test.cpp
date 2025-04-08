#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool iflike(string& s, string& t, int k) {
        // 取出t的前k个字母
        int n = t.size();
        if (n < k) return false;
        string subt = t.substr(0, k);
        if(s.find(subt) != string::npos) return true;
        subt = t.substr(n-k, k);
        reverse(subt.begin(), subt.end());
        reverse(s.begin(), s.end());
        if(s.find(subt) != string::npos) return true;
        return false;
    }
};

int main() {
    string s;
    cin >> s;
    int num, k;
    cin >> num >> k;
    Solution solution;
    for (int i = 0; i < k; i++) {
        string t;
        cin >> t;
        if (solution.iflike(s, t, k)) {
            cout << "YES" << endl;
        }else {
            cout << "NO" << endl;
        }
    }
    return 0;
}