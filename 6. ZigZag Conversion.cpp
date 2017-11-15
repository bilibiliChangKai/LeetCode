/*
 * 坑点：numRows可能为1
 *       输入字符串为空 
 */

#include <iostream>
#include <string>
using namespace std;

string convert(string s, int numRows) {
    string cvString;                     // 转换后的string
    int jumpSize = 2 * (numRows - 1);    // 一个字符到下一个之字型对应字符的间隔 
    
    // 特殊情况：numRows=1
    if (numRows == 1)  return s; 
    
    // 第一行
    for (int i = 0; i < s.length(); i += jumpSize)
        cvString.push_back(s[i]);
        
    // 第二行~第numRows-1行，每个之字型中间包含一个字符，因此要取两次 
    for (int i = 2; i < numRows; i++) {
        // 起始字符位置为i-1 
        int j = i - 1;
        while (1) {
            if (j >= s.length())  break;
            cvString.push_back(s[j]);
            j += jumpSize - 2 * (i - 1);
            
            if (j >= s.length())  break;
            cvString.push_back(s[j]);
            j += 2 * (i - 1);
        } 
    } 
    
    // 最后一行
    for (int i = numRows - 1; i < s.length(); i += jumpSize)
        cvString.push_back(s[i]);
        
    return cvString;
}

void addTestData(string& str, int& rows) {
    str = "A";
    rows = 1;
}

void showOutput(string output) {
    cout << output << endl;
}

int main() {
    string str;
    int rows;
    addTestData(str, rows);
    showOutput(convert(str, rows)); 
}
