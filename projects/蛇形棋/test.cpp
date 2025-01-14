#include<queue>
#include<vector>

using namespace std;

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        queue<int> snake_q;
        int curr = 1, n = board.size(), currChoice = 1, currDepth = 1;
        if (board.size() != 0) snake_q.push(1);
        while (curr != n*n && !snake_q.empty()) {
            int nextChoice = 0;
            for (int i = 0; i < currChoice; i++) {
                int curr = snake_q.front();
                // 对于每个choice，除了+1~6，还需要做蛇/梯子的选择。
                for (int j = 1; j < 6 && j + curr <= n*n; j++) {
                    int nextPos = curr + j;
                    if (nextPos == n * n) return currDepth;
                    int nextI = (n*n - nextPos) / n;
                    int nextJ = 0;
                    if (nextI % 2 == 0) { // 逆着走
                        nextJ = n*n - nextPos - nextI * n;
                    }else { // 顺着走
                        nextJ = n - (n*n - nextPos - nextI * n);
                    }
                    if (board[nextI][nextJ] != -1) {
                        snake_q.push(board[nextI][nextJ]);
                    }else {
                        snake_q.push(nextPos);
                    }
                    nextChoice++;
                }
                currDepth++;
            }
            currChoice = nextChoice;
        }
        return 0;
    }
};