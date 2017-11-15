#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Solution {
public:
//    int longestSubstring(string x, string y) {
//       
//       }
};

int longestSubstring(string x, string y) {
    int maxLength = 0;
    // isEqual[i][j] 表示x的前i个字符与y的前j个字符的最后子串匹配的长度 
    int **isEqual = new int*[x.length()];
    for (int i = 0; i < x.length(); i++)
        isEqual[i] = new int[y.length()];
    
    // 对第一个字符串赋值 
    for (int i = 0; i < x.length(); i++)
        isEqual[i][0] = x[i] == y[0];
    for (int j = 0; j < y.length(); j++)
        isEqual[0][j] = x[0] == y[j];
    
    for (int i = 1; i < x.length(); i++) {
        for (int j = 1; j < y.length(); j++) {
            isEqual[i][j] = x[i] == y[j] ? isEqual[i - 1][j - 1] + 1 : 0;
            if (isEqual[i][j] > maxLength)  maxLength = isEqual[i][j];
        }
    }
    
    return maxLength;
}

void addTestData(string &a, string &b) {
    a = "introduction";
    b = "introductive";
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    string a, b;
    addTestData(a, b);
    showOutput(longestSubstring(a, b)); 
}
