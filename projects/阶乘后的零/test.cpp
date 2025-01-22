

// 法1：数每个数中因子5的个数
class Solution {
public:
    int trailingZeroes(int n) {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (i % 5 == 0) {
                int currNum = i;
                while (currNum != 0 && currNum % 5 == 0) {
                    res++;
                    currNum /= 5;
                }
            }
        }
        return res;
    }
};

// 法1基础上修改：从5开始，每次加5
class Solution2 {
public:
    int trailingZeroes(int n) {
        int res = 0;
        for (int i = 5; i <= n; i+=5) {
            for (int currNum = i; currNum != 0 && currNum % 5 == 0; currNum /= 5) {
                res++;
            }
        }
        return res;
    }
};