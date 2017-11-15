#include <iostream>
#include <bitset>
using namespace std;

int IP_Table[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                    60, 52, 44, 36, 28, 20, 12, 4,
                    62, 54, 46, 38, 30, 22, 14, 6,
                    64, 56, 48, 40, 32, 24, 16, 8,
                    57, 49, 41, 33, 25, 17, 9,  1,
                    59, 51, 43, 35, 27, 19, 11, 3,
                    61, 53, 45, 37, 29, 21, 13, 5,
                    63, 55, 47, 39, 31, 23, 15, 7};

int IP_1_Table[64] = {40, 8,  48, 16, 56, 24, 64, 32,
                      39, 7,  47, 15, 55, 23, 63, 31,
                      38, 6,  46, 14, 54, 22, 62, 30,
                      37, 5,  45, 13, 53, 21, 61, 29,
                      36, 4,  44, 12, 52, 20, 60, 28,
                      35, 3,  43, 11, 51, 19, 59, 27,
                      34, 2,  42, 10, 50, 18, 58, 26,
                      33, 1,  41, 9,  49, 17, 57, 25};

int PC_1_Table[56] = {57, 49, 41, 33, 25, 17, 9,
                      1,  58, 50, 42, 34, 26, 18,
                      10, 2,  59, 51, 43, 35, 27,
                      19, 11, 3,  60, 52, 44, 36,
                      63, 55, 47, 39, 31, 23, 15,
                      7,  62, 54, 46, 38, 30, 22,
                      14, 6,  61, 53, 45, 37, 29,
                      21, 13, 5,  28, 20, 12, 4 };

int PC_2_Table[48] = {14, 17, 11, 24, 1,  5,
                      3,  28, 15, 6,  21, 10,
                      23, 19, 12, 4,  26, 8,
                      16, 7,  27, 20, 13, 2,
                      41, 52, 31, 37, 47, 55,
                      30, 40, 51, 45, 33, 48,
                      44, 49, 39, 56, 34, 53,
                      46, 42, 50, 36, 29, 32};

int E_Table[48] = {32, 1,  2,  3,  4,  5,
                   4,  5,  6,  7,  8,  9,
                   8,  9,  10, 11, 12, 13,
                   12, 13, 14, 15, 16, 17,
                   16, 17, 18, 19, 20, 21,
                   20, 21, 22, 23, 24, 25,
                   24, 25, 26, 27, 28, 29,
                   28, 29, 30, 31, 32, 1 };

int P_Table[32] = {16, 7,  20, 21,
                   29, 12, 28, 17,
                   1,  15, 23, 26,
                   5,  18, 31, 10,
                   2,  8,  24, 14,
                   32, 27, 3,  9, 
                   19, 13, 30, 6,
                   22, 11, 4,  25};

int S_Table[8][4][16] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                         0, 15, 7, 4, 15, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                         4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                         15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
                         
                         15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                         3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                         0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                         13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
                         
                         10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                         13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                         13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                         1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
                         
                         7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                         12, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                         10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                         3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
                         
                         2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                         14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                         4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                         11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
                         
                         12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                         10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                         9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                         4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
                         
                         4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                         13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                         1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                         6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
                         
                         13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                         1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                         7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                         2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

// IP置换
bitset<64> IP_Replacement(bitset<64> input) {
    bitset<64> output;
    for (int i = 0; i < 64; i++)
        output[i] = input[IP_Table[i] - 1];
    return output;
}

// IP逆置换 
bitset<64> IP_1_Replacement(bitset<64> input) {
    bitset<64> output;
    for (int i = 0; i < 64; i++)
        output[i] = input[IP_1_Table[i] - 1];
    return output;
}

// PC-1函数 
bitset<56> PC_1(bitset<56> input) {    
    bitset<56> output;
    for (int i = 0; i < 56; i++)
        output[i] = input[IP_1_Table[i] - 1];
    return output;
}

// PC-2函数 
bitset<48> PC_2(bitset<48>& input) {
    bitset<48> output;
    for (int i = 0; i < 48; i++)
        output[i] = input[IP_1_Table[i] - 1];
    return output;
}

// E扩展函数 
bitset<48> E_Extension(bitset<32> input) {
    bitset<48> output;
    for (int i = 0; i < 48; i++)
        output[i] = input[E_Table[i] - 1];
    return output;
}

// S-Box缩减 
bitset<32> S_Box(bitset<48> input) {
    bitset<32> output;
    for (int i = 0; i < 8; i++) {
        bitset<2> row;
        bitset<4> col;
        row[0] = input[i * 6];
        row[1] = input[i * 6 + 1];
        for (int j = 0; j < 4; j++)
            col[j] = input[i * 6 + j + 1];
        
        bitset<4> box;
        box = S_Table[i][row.to_ulong()][col.to_ulong()] - 1;
        for (int j = 0; j < 4; j++)
            output[4 * i + j] = box[j];
    }
    
    return output;
}

// P置换
void P_Replacement(bitset<32>& input) {
    input = P_Table[31 - input.to_ulong()] - 1;
} 

// 左右各左移一位 
void shiftToLeft(bitset<56>& input) {
    bool temp;
    temp = input[27];
    for (int i = 27; i > 0; i--)
        input[i] = input[i - 1];
    input[0] = temp;
    
    temp = input[55];
    for (int i = 27; i > 0; i--)
        input[i + 28] = input[i + 27];
    input[28] = temp;
}

// 此函数用于生成密钥，getKeys :: K -> [k1, ... ,k16](keys) 
void getKeys(bitset<64> K, bitset<48> keys[]) {
    bitset<56> K1;
    // 去掉校验位（每个字节最后一位），得到K1 
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 7; j++)  K1[i * 7 + j] = K[i * 8 + j + 1];


    // PC-1
    PC_1(K1);
    
    for (int i = 1; i <= 16; i++) {
        // 循环置换
        if (i == 1 || i == 2 || i == 9 || i == 16)  shiftToLeft(K1);
        shiftToLeft(K1);
        
        // 减去其中8位，得到K2 
        bitset<48> K2;
        int j, k;
        for (j = 0, k = 0; j < 56; j++, k++) {
            if (j == 9 || j == 18 || j == 22 || j == 25 ||
                j == 35 || j == 18 || j == 13 || j == 2)  j++;
            K2[k] = K1[j];
        }
        
        // PC-2
        PC_2(K2);
        
        keys[i - 1] = K2;
    }
}

// Feistal轮函数 
bitset<32> feistal(bitset<32> R, bitset<48> k) {
    bitset<32> output = S_Box(E_Extension(R) ^ k);
    P_Replacement(output);
    return output;
}

// T迭代 
bitset<64> T_Iteration(bitset<64> LR, bitset<48> k) {
    bitset<64> RL;
    bitset<32> R, L;
    
    for (int i = 0; i < 32; i++)  L[i] = LR[i];
    for (int i = 0; i < 32; i++)  R[i] = LR[i + 32];
    
    R = feistal(R, k) ^ R;
    
    for (int i = 0; i < 32; i++) {
        RL[i] = R[i];
        RL[32 + i] = L[i];
    }
    
    return RL;
}

bitset<64> encryption(bitset<64> message, bitset<64> K) {
    bitset<48> keys[16];
    bitset<64> cryptograph = message;
    
    // 产生k1..k16 
    getKeys(K, keys);
    
    // IP置换 
    IP_Replacement(cryptograph);
    
    // T1 - T16 迭代 
    for (int i = 0; i < 16; i++)
        cryptograph = T_Iteration(cryptograph, keys[i]);
    
    // LR->RL
    bool temp;
    for (int i = 0; i < 32; i++) {
        temp = cryptograph[i];
        cryptograph[i] = cryptograph[i + 32];
        cryptograph[i + 32] = temp;
    }
    
    // IP逆置换 
    IP_1_Replacement(cryptograph);
    
    return cryptograph;
}

bitset<64> decryption(bitset<64> cryptograph, bitset<64> K) {
    bitset<48> keys[16];
    bitset<64> message = cryptograph;
    
    // 产生k1..k16 
    getKeys(K, keys);
    
    // IP逆置换 
    IP_1_Replacement(message);
    
    // T16 - T1 迭代 
    for (int i = 15; i >= 0; i--)
        message = T_Iteration(message, keys[i]);
    
    // IP置换 
    IP_Replacement(message);
    
    return message;
}

int main() {
    string str("0001010001100000000000001111111100000000000001011110");
    bitset<64> message(str);
    bitset<64> cryptograph;
    bitset<64> K(str);
    cout << "message:" << message << endl;
    cryptograph = encryption(message, K);
    cout << "cryptograph:" << cryptograph << endl;
}
