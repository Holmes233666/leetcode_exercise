class Solution {
public:
    int mySqrt(int x) {
        return binarySearch(0, x, x);
    }

    int binarySearch(int start, int end, long x) {
        if (start <= end) {
            long mid = (start + end) / 2;
            if (mid * mid == x) return mid;
            if (mid * mid > x) return binarySearch(start, mid-1, x);
            return binarySearch(mid+1, end, x);
        }
        return end;
    }
};
