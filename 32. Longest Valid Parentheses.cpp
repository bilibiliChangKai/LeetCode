#include <iostream>
#include <stack>
using namespace std;

// 用栈解决 

int longestValidParentheses(string s) {
    int longestLength = 0;                // 储存最长长度
    int validStringEnd;                   // 记录有效字符串的终点，用于遍历栈 
    stack<pair<char, int>> sta;           // 用于匹配()的栈，后一个int值记录该符号在字符串s中的位置 
    
    for (int i = 0; i < s.length(); i++) {
        // 如果为'('，入栈 
        if (s[i] == '(') {
            pair<char, int> p('(', i);
            sta.push(p);
        }
        // 如果为')'
        else {
            // 判断栈顶是否为'('，如果是，出栈，同时意为存在一个()匹配
            if (!sta.empty() && sta.top().first == '(')
                sta.pop();
            // 不是，则字符串未匹配，子串匹配结束 
            else {
                pair<char, int> p(')', i);
                sta.push(p);
            }
        }
    } 
    
    // 最后栈中剩下的就是无法匹配的部分，可以获得这些字符在s中的位置
    // 栈底的位置前，栈顶的位置后，按顺序排列 
    // 两个相邻的位置之间存在一个有效字符串
     
    validStringEnd = s.length();
    // 依次遍历这些字符串的长度，得到最大值 
    while (!sta.empty()) {
        pair<char, int> p = sta.top();
        sta.pop();
        if (validStringEnd - p.second - 1 > longestLength)
            longestLength = validStringEnd - p.second - 1;
        validStringEnd = p.second;
    }
    
    // 开头匹配 
    if (validStringEnd - 0 > longestLength)
        longestLength = validStringEnd - 0;
    
    return longestLength;
}

void addTestData(string &s) {
    s = ")";
}

void outputData(int data) {
    cout << data << endl;
}

int main() {
    string s;
    addTestData(s);
    outputData(longestValidParentheses(s));
} 
