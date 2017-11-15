#include <iostream>
using namespace std;

// 原型: int atoi(const char *nptr);
// 函数说明: 参数nptr字符串，如果第一个非空格字符不存在或者
// 不是数字也不是正负号则返回零，否则开始做类型转换，之后检
// 测到非数字(包括结束符 \0) 字符时停止转换，返回整型数。 

// 坑点：
//   1.从第一个非空格字符开始
//   2.无法越界，取值范围有限制 
//   3.可以识别"+123"之类的正数 

int myAtoi(string str) {
    bool isNegative = false;     // 表示正负
    long long output = 0;     // 表示输出值 
    
    // 如果输入为空
    if (str.empty())  return output;
    
    // 寻找第一个空格后字符位置 
    int i;
    for (i = 0; i < str.length(); i++)
        if (str[i] != ' ')  break;
    
    // 没有找到，返回0
    if (i == str.length())  return output;
    else if (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')  isNegative = true;
        i++;
    } 
    else if (!isdigit(str[i]))  return output;
    
    // 进行字符相加
    while (i < str.length() && isdigit(str[i])) {
        output *= 10;
        output += str[i] - '0';
        i++;
        
        // 判断是否越界 
        if (output > 2147483648) {
            output = 2147483648;
            break;
        }
    }
    
    // 添加正负号，int取值范围为-2^32----2^32-1 
    if (!isNegative) {
        if (output == 2147483648)  output--;
    }
    else  output = -output;
    
    return (int)output;
}

void addTestData(string& rows) {
    rows = "-2147483649";
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    string rows;
    addTestData(rows);
    showOutput(myAtoi(rows)); 
}
