#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

// 用排除法解出数独的答案
// 1.遍历数组，找到只能填写唯一可能数字的格子
// 2.将该格子填上数字
// 3.遍历该格子同行同列同宫，判断是否出现(1)中的格子，如果是，重复(2)(3)
// 4.如果剩余格子不为0，重新执行(1)

void outputData(vector<vector<char>>& board);
void outputTest(vector<vector<char>>& board);


// 从左往右，从上到下分为9宫，在这里为0-8 
int getSquareNumber(int i, int j) {
    return i / 3 * 3 + j / 3;
}

// 得到i，j位方格的Bitset 
bitset<9> getSquareBitset(int i, int j, bitset<9>* row, bitset<9>* col, bitset<9>* squ) {
    return row[i] | col[j] | squ[getSquareNumber(i, j)];
}

// 判断该位置是否只有唯一解 
bool hasUniqueAnswer(int i, int j, bitset<9>* row, bitset<9>* col, bitset<9>* squ) {
    return (getSquareBitset(i, j, row, col, squ)).count() == 8;
}

// 判断该位置是否无解 
bool hasNoAnswer(int i, int j, bitset<9>* row, bitset<9>* col, bitset<9>* squ) {
    return (getSquareBitset(i, j, row, col, squ)).count() == 9;
}

// 返回当前数独的状态，-1代表已经无解，0代表可能有解，1代表已经解出 
int getProblemState(vector<vector<char>>& board, bitset<9>* row,
                    bitset<9>* col, bitset<9>* squ) {
    int state = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // 若不存在'.'，意为解出答案 
            if (board[i][j] == '.') {
                state = 0;
                // 如果有一个'.'无解，则无解 
                if (hasNoAnswer(i, j, row, col, squ))
                    return -1;
            }
        }
    }
    return state;
}

// 根据数独设置rows，cols，squs和remainEmptyNum
void setEnvironment(vector<vector<char>>& board, bitset<9>* row,
                    bitset<9>* col, bitset<9>* squ, int &remainEmptyNum) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                remainEmptyNum++;
                continue;
            }
            int num = board[i][j] - '1';
            // 设置行 
            row[i].set(num);
            // 设置列 
            col[j].set(num);
            // 设置宫
            squ[getSquareNumber(i, j)].set(num);
        }
    } 
}

// 填充唯一解的方格，并递归寻找同行，同列，同宫的方格 
void recurSolveUniqueAnswer(vector<vector<char>>& board, int i, int j,
                    bitset<9>* row, bitset<9>* col, bitset<9>* squ) {
    int seqIndex = getSquareNumber(i, j);
    bitset<9> temp = row[i] | col[j] | squ[seqIndex]; 
    
    // 查找该值 
    int t;
    for (t = 0; t < 9; t++)
        if (!temp.test(t))  break;
    
    // 修改bitsets，board，remainEmptyNum 
    row[i].set(t);
    col[j].set(t);
    squ[seqIndex].set(t);
    board[i][j] = t + '1';
    
    // 递归求解 
    for (t = 0; t < 9; t++) {
        // 同行递归 
        if (board[i][t] == '.' && hasUniqueAnswer(i, t, row, col, squ))
            recurSolveUniqueAnswer(board, i, t, row, col, squ);
        // 同列递归 
        if (board[t][j] == '.' && hasUniqueAnswer(t, j, row, col, squ))
            recurSolveUniqueAnswer(board, t, j, row, col, squ);
        // 同宫递归
        int rowIndex = seqIndex / 3 * 3 + t / 3;
        int colIndex = seqIndex % 3 * 3 + t % 3;
        if (board[rowIndex][colIndex] == '.' && hasUniqueAnswer(rowIndex, colIndex, row, col, squ)) 
            recurSolveUniqueAnswer(board, rowIndex, colIndex, row, col, squ);
    }
}

// 递归求解问题，并返回是否有解 
bool recurSolveProblem(vector<vector<char>>& board,
                bitset<9>* row, bitset<9>* col, bitset<9>* squ) {

                    
    // 找出是否存在唯一解，若有，进行求解并填充 
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j] == '.' && hasUniqueAnswer(i, j, row, col, squ))
                recurSolveUniqueAnswer(board, i, j, row, col, squ);
    
    // 基本情况：已经出现结果 
    int state = getProblemState(board, row, col, squ);
    if (state != 0)  return state == 1;
    
    // 递归情况：找到最少可能性的方格对所有可能性进行递归
    
    // 找到最小可能性的方格 
    int r, c;
    bitset<9> minBitset;
    minBitset.set(); 
    bitset<9> temp;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                temp = getSquareBitset(i, j, row, col, squ);
                if (temp.count() < minBitset.count()) {
                    minBitset = temp;
                    r = i;
                    c = j;
                }
            }
        }
    }
    
    // 对其中可能出现的情况依次递归 
    for (int i = 0; i < 9; i++) {
        if (!minBitset.test(i)) {
            // 复制初始环境
            vector<vector<char>> cboard = board;
            bitset<9> crow[9], ccol[9], csqu[9];
            for (int i = 0; i < 9; i++) {
                crow[i] = row[i];
                ccol[i] = col[i];
                csqu[i] = squ[i];
            }
            
            // 假设该位填写数字(i + 1) 
            crow[r].set(i);
            ccol[c].set(i);
            csqu[getSquareNumber(r, c)].set(i);
            cboard[r][c] = i + '1';
            
            // 递归解出题目 
            if (recurSolveProblem(cboard, crow, ccol, csqu)) {
                // 返回true，并复制答案 
                board.clear();
                board = cboard;
                return true;
            }
        }
    }
    
    // 遍历所有可能都没有得出答案，则错误发生在之前的步骤 
    return false;
}

void solveSudoku(vector<vector<char>>& board) {
    int remainEmptyNum;                // 剩下未填写的格子
    bitset<9> row[9], col[9], squ[9];  // 用于表示第i行，第i列，第i宫已填写数字情况
                                       // 第j个bit为1，代表数字j已填写
    
    // 初始化条件 
    setEnvironment(board, row, col, squ, remainEmptyNum);
    
    // 递归寻找解
    recurSolveProblem(board, row, col, squ);
}

void addTestData(vector<vector<char>>& board) {
    string data[9] = {"..9748...",
                      "7..6.2...",
                      ".2.1.9...",
                      "..7986241",
                      "264317598",
                      "198524367",
                      "...863.2.",
                      "...491..6",
                      "...2759.."};
    string answ[9] = {"519748632",
                      "783652419",
                      "426139875",
                      "357986241",
                      "264317598",
                      "198524367",
                      "975863124",
                      "832491756",
                      "641275983"};
    for (int i = 0; i < 9; i++) {
        vector<char> temp;
        for (int j = 0; j < 9; j++) {
            temp.push_back(data[i][j]);
        }
        board.push_back(temp);
    }
} 

void outputData(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void outputTest(vector<vector<char>>& board, bitset<9>* row,
                    bitset<9>* col, bitset<9>* squ) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.')  cout << "xxxxxxxxx ";
            else  cout << (row[i] | col[j] | squ[getSquareNumber(i, j)]) << " ";
        }
        cout << endl << endl;
    }                    
}

int main() {
    vector<vector<char>> board;
    addTestData(board);
    solveSudoku(board);
    outputData(board);
}
