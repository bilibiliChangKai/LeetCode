#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

// ���ų�����������Ĵ�
// 1.�������飬�ҵ�ֻ����дΨһ�������ֵĸ���
// 2.���ø�����������
// 3.�����ø���ͬ��ͬ��ͬ�����ж��Ƿ����(1)�еĸ��ӣ�����ǣ��ظ�(2)(3)
// 4.���ʣ����Ӳ�Ϊ0������ִ��(1)

void outputData(vector<vector<char>>& board);
void outputTest(vector<vector<char>>& board);


// �������ң����ϵ��·�Ϊ9����������Ϊ0-8 
int getSquareNumber(int i, int j) {
    return i / 3 * 3 + j / 3;
}

// �õ�i��jλ�����Bitset 
bitset<9> getSquareBitset(int i, int j, bitset<9>* row, bitset<9>* col, bitset<9>* squ) {
    return row[i] | col[j] | squ[getSquareNumber(i, j)];
}

// �жϸ�λ���Ƿ�ֻ��Ψһ�� 
bool hasUniqueAnswer(int i, int j, bitset<9>* row, bitset<9>* col, bitset<9>* squ) {
    return (getSquareBitset(i, j, row, col, squ)).count() == 8;
}

// �жϸ�λ���Ƿ��޽� 
bool hasNoAnswer(int i, int j, bitset<9>* row, bitset<9>* col, bitset<9>* squ) {
    return (getSquareBitset(i, j, row, col, squ)).count() == 9;
}

// ���ص�ǰ������״̬��-1�����Ѿ��޽⣬0��������н⣬1�����Ѿ���� 
int getProblemState(vector<vector<char>>& board, bitset<9>* row,
                    bitset<9>* col, bitset<9>* squ) {
    int state = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // ��������'.'����Ϊ����� 
            if (board[i][j] == '.') {
                state = 0;
                // �����һ��'.'�޽⣬���޽� 
                if (hasNoAnswer(i, j, row, col, squ))
                    return -1;
            }
        }
    }
    return state;
}

// ������������rows��cols��squs��remainEmptyNum
void setEnvironment(vector<vector<char>>& board, bitset<9>* row,
                    bitset<9>* col, bitset<9>* squ, int &remainEmptyNum) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                remainEmptyNum++;
                continue;
            }
            int num = board[i][j] - '1';
            // ������ 
            row[i].set(num);
            // ������ 
            col[j].set(num);
            // ���ù�
            squ[getSquareNumber(i, j)].set(num);
        }
    } 
}

// ���Ψһ��ķ��񣬲��ݹ�Ѱ��ͬ�У�ͬ�У�ͬ���ķ��� 
void recurSolveUniqueAnswer(vector<vector<char>>& board, int i, int j,
                    bitset<9>* row, bitset<9>* col, bitset<9>* squ) {
    int seqIndex = getSquareNumber(i, j);
    bitset<9> temp = row[i] | col[j] | squ[seqIndex]; 
    
    // ���Ҹ�ֵ 
    int t;
    for (t = 0; t < 9; t++)
        if (!temp.test(t))  break;
    
    // �޸�bitsets��board��remainEmptyNum 
    row[i].set(t);
    col[j].set(t);
    squ[seqIndex].set(t);
    board[i][j] = t + '1';
    
    // �ݹ���� 
    for (t = 0; t < 9; t++) {
        // ͬ�еݹ� 
        if (board[i][t] == '.' && hasUniqueAnswer(i, t, row, col, squ))
            recurSolveUniqueAnswer(board, i, t, row, col, squ);
        // ͬ�еݹ� 
        if (board[t][j] == '.' && hasUniqueAnswer(t, j, row, col, squ))
            recurSolveUniqueAnswer(board, t, j, row, col, squ);
        // ͬ���ݹ�
        int rowIndex = seqIndex / 3 * 3 + t / 3;
        int colIndex = seqIndex % 3 * 3 + t % 3;
        if (board[rowIndex][colIndex] == '.' && hasUniqueAnswer(rowIndex, colIndex, row, col, squ)) 
            recurSolveUniqueAnswer(board, rowIndex, colIndex, row, col, squ);
    }
}

// �ݹ�������⣬�������Ƿ��н� 
bool recurSolveProblem(vector<vector<char>>& board,
                bitset<9>* row, bitset<9>* col, bitset<9>* squ) {

                    
    // �ҳ��Ƿ����Ψһ�⣬���У�������Ⲣ��� 
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j] == '.' && hasUniqueAnswer(i, j, row, col, squ))
                recurSolveUniqueAnswer(board, i, j, row, col, squ);
    
    // ����������Ѿ����ֽ�� 
    int state = getProblemState(board, row, col, squ);
    if (state != 0)  return state == 1;
    
    // �ݹ�������ҵ����ٿ����Եķ�������п����Խ��еݹ�
    
    // �ҵ���С�����Եķ��� 
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
    
    // �����п��ܳ��ֵ�������εݹ� 
    for (int i = 0; i < 9; i++) {
        if (!minBitset.test(i)) {
            // ���Ƴ�ʼ����
            vector<vector<char>> cboard = board;
            bitset<9> crow[9], ccol[9], csqu[9];
            for (int i = 0; i < 9; i++) {
                crow[i] = row[i];
                ccol[i] = col[i];
                csqu[i] = squ[i];
            }
            
            // �����λ��д����(i + 1) 
            crow[r].set(i);
            ccol[c].set(i);
            csqu[getSquareNumber(r, c)].set(i);
            cboard[r][c] = i + '1';
            
            // �ݹ�����Ŀ 
            if (recurSolveProblem(cboard, crow, ccol, csqu)) {
                // ����true�������ƴ� 
                board.clear();
                board = cboard;
                return true;
            }
        }
    }
    
    // �������п��ܶ�û�еó��𰸣����������֮ǰ�Ĳ��� 
    return false;
}

void solveSudoku(vector<vector<char>>& board) {
    int remainEmptyNum;                // ʣ��δ��д�ĸ���
    bitset<9> row[9], col[9], squ[9];  // ���ڱ�ʾ��i�У���i�У���i������д�������
                                       // ��j��bitΪ1����������j����д
    
    // ��ʼ������ 
    setEnvironment(board, row, col, squ, remainEmptyNum);
    
    // �ݹ�Ѱ�ҽ�
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
