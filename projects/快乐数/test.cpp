#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        // 使用字符串存储n，方便提取数字
        string currNumStr = to_string(n);
        sort(currNumStr.begin(), currNumStr.end());
        unordered_map<string, bool> umap;
        umap[currNumStr] = true;
        while(true) {
            string newStr;
            int accumulateNum = 0, len = currNumStr.size();
            for (int i = 0; i < len; i++) {
                accumulateNum += pow(currNumStr[i] - '0', 2);
            }
            if (accumulateNum == 1) return true;
            newStr = to_string(accumulateNum);
            // 对newStr排序
            sort(newStr.begin(), newStr.end());
            if (umap.find(newStr) != umap.end()) {  // 已经有这个数字了
                return false;
            }
            umap[newStr] = true; // 没有这个数
            currNumStr = newStr;
        }
        return false;
    }
};


// 法2：快慢指针
class Solution2 {
public:
    bool isHappy(int n) {
        int fast = getNext(n), slow = n;
        while (fast != slow && fast != 1) {
            slow = getNext(slow);                  // 每次走一步
            fast = getNext(getNext(fast));     // 每次走两步
        }
        return fast == 1;
    }

    int getNext(int n) {
        int res = 0;
        while(n > 0) {
            int d = n % 10;
            n = n / 10;
            res += d * d;
        }
        return res;
    }
};
