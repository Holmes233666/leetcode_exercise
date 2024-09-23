#include<stack>

using namespace std;

class MinStack {
public:
    stack<int> numStack, miniStack;
    int miniNum;
    MinStack() {
        miniNum = INT_MAX;
    }

    void push(int val) {
        numStack.emplace(val);
        if (val < miniNum) {
            miniNum = val;
        }
        miniStack.emplace(miniNum);
    }

    void pop() {
        numStack.pop();
        miniStack.pop();
    }

    int top() {
        return numStack.top();
    }

    int getMin() {
        return miniStack.top();
    }
};

int main() {

    return 0;
}
