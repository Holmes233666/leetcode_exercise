class Solution {
public:
    double myPow(double x, int n) {
        return myPow(x, n);
    }
    double divide(double x, int n) {
        if (n % 2 == 0) {
            int half = n / 2;
            double halfRes = divide(x, half);
            return halfRes * halfRes;
        }
        int half = n / 2;
        double halfRes = divide(x, half);
        return halfRes * halfRes * x;
    }
};

