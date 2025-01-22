

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int move = 0;
        while (left != right) {
            left >>= 1;
            right >>= 1;
            move++;
        }
        // 直到找到最长公共前缀，后位补0
        while (move--) {
            left <<= 1;
        }
        return left;
    }
};
