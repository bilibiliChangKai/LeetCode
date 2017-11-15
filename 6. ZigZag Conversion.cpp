/*
 * �ӵ㣺numRows����Ϊ1
 *       �����ַ���Ϊ�� 
 */

#include <iostream>
#include <string>
using namespace std;

string convert(string s, int numRows) {
    string cvString;                     // ת�����string
    int jumpSize = 2 * (numRows - 1);    // һ���ַ�����һ��֮���Ͷ�Ӧ�ַ��ļ�� 
    
    // ���������numRows=1
    if (numRows == 1)  return s; 
    
    // ��һ��
    for (int i = 0; i < s.length(); i += jumpSize)
        cvString.push_back(s[i]);
        
    // �ڶ���~��numRows-1�У�ÿ��֮�����м����һ���ַ������Ҫȡ���� 
    for (int i = 2; i < numRows; i++) {
        // ��ʼ�ַ�λ��Ϊi-1 
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
    
    // ���һ��
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
