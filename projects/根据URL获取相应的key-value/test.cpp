#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    string getValue(string& url, string& key) {
        // 首先将url按照?分割
        int idx = url.find('?');
        string substr = url.substr(idx+1);  // 提取问号后的部分
        // 获取以 '=' 分割的各个部分
        string str;
        stringstream ss(substr);
        string k, v;
        while(getline(ss, str, '&')) {
            stringstream tempss(str);
            if (getline(tempss, k, '=') && getline(tempss, v)) {    // 注意用法，第一个getline返回遇到第一个等于之前的所有内容，即key，第二个getline返回剩余的内容
                if (key == k) {
                    return v;
                }
            }
        }
        return "";
    }
};


int main() {
    // 测试样例： https://example.com/page?name=John&age=25&city=NewYork&lang=C++ name
    string url, key;
    cin >> url >> key;
    Solution s;
    cout << s.getValue(url, key) << endl;
    return 0;
}
