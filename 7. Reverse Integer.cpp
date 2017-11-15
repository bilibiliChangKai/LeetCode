#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int reverse(int x) {
    bool isNegative = x < 0;      // 判断正负 
    x = abs(x);
    
    char contain[100];            // 作为中转站
    sprintf(contain, "%d", x);
    
    // 字符串反转 
    int length;
    for (int i = 0; i < 100; i++)
        if (contain[i] == '\0') {
            length = i;
            break;
        }
    for (int i = 0; i < length / 2; i++) {
        char temp = contain[i];
        contain[i] = contain[length - i - 1];
        contain[length - i - 1] = temp;
    }
    
    long output;          // 由于会超过2^31-1，用long比较 
    sscanf(contain, "%ld", &output);
    
    // 重新添加正负 
    if (isNegative)  output = -output;
    
    // 判断是否越界 
    if (output > pow(2, 31) - 1 || output < -pow(2, 31))  output = 0;
    
    return (int)output;
} 

void addTestData(int& rows) {
    rows = -12345679;
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    int rows;
    addTestData(rows);
    showOutput(reverse(rows)); 
}
