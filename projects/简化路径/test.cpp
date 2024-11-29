#include<vector>
#include<stack>
#include<sstream>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        // 首先对path进行按照/的划分
        stringstream ss(path);
        vector<string> stringVec;
        string segment;
        while (getline(ss, segment, '/')) {
            stringVec.push_back(segment);
        }
        int n = stringVec.size(), currIdx = 1;
        vector<string> resPath = {"/"}; // 结果存在vec中，方便正向读取连接最终结果
        while (currIdx < n) {
            while (currIdx < n && stringVec[currIdx] == "") {
                currIdx++;
            }
            if (currIdx >= n) break;
            if (stringVec[currIdx] == ".") {    // 当前目录，直接跳过
                currIdx++;
            }else if (stringVec[currIdx] == "..") {
                if (resPath.size() != 1) {  // 如果不是根目录
                    resPath.pop_back(); // 弹出 “/"
                    resPath.pop_back(); // 弹出字符
                }
                currIdx++;
            }else { // 其他字符直接当做正常字符处理
                resPath.push_back(stringVec[currIdx]);
                if (currIdx != n-1) {
                    resPath.push_back("/");
                }
                currIdx++;
            }
        }
        // 遍历数组，合并产生正确的结果
        string res;
        for (int j = 0; j < resPath.size(); j++) {
            if (j == resPath.size()-1 && resPath[j] == "/" && resPath.size() != 1) break;
            res += resPath[j];
        }
        return res;
    }
};

// int n = path.size(), currIdx = 0;
// stack<char> pathStack;
// while (currIdx < n) {
//     if (path[currIdx] == '/' && (pathStack.empty() || pathStack.top() != '/')) { // 如果是单斜杠，判断在栈非空的情况下保证只放进去一个'/'，或者栈空直接入栈
//         pathStack.emplace('/');
//         currIdx++;
//     }else if (path[currIdx] == '.') {
//         // 如果只有一个点：直接跳过
//         if (currIdx + 1 == n || currIdx + 1 < n && path[currIdx + 1] == '/') {
//             currIdx += 2;
//         }else if (currIdx + 1 < n && path[currIdx + 1] != '/') {   // 如果是一个点，但是后面还有别的字符
//             while (currIdx < n && path[currIdx] != '/') {    // 一直入栈
//                 pathStack.emplace(path[currIdx]);
//                 currIdx++;
//             }
//         }else if (currIdx + 1 < n && path[currIdx + 1] == '.')
//     }
// }