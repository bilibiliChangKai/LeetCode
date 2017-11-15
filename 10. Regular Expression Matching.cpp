#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * 坑点:
 * 1. 空对空
 * 2. 空对可以转换成空的字符
 * 3. *不一定要匹配所有相同的字符 
 */ 

bool isEqual(char a, char b) {
    return a == b || b == '.';
}

// 递归求解，每次只判断一个字符，isfirst用于判断是否有子串匹配成功了 
bool recur(string &s, string &p, int sbegin, int pbegin) {
    // 基础情况：s为空，即第一次匹配成功 
    if (s.size() - sbegin == 0) {
        if (p.size() - pbegin == 0)  return true;
        else if (p.size() - pbegin >= 2 && p[pbegin + 1] == '*')
            return recur(s, p, sbegin, pbegin + 2);
        return false;
    }
    
    // 基础情况：p为空，s不为空 
    if (p.size() - pbegin == 0)  return false;
    
    // 递归情况
    // 情况1：遇到星号 （此处可用递归） 
    if (pbegin + 1 < p.size() && p[pbegin + 1] == '*') {
        // 如果之后有其中之一完全匹配，即完全匹配 
        int i;
        // 匹配1-n个相同字符 
        for (i = sbegin; i < s.size() && isEqual(s[i], p[pbegin]); i++)
            if (recur(s, p, i, pbegin + 2))  return true;
        // 匹配所有相同字符，或者字符根本不相同 
        return recur(s, p, i, pbegin + 2); 
    }
    
    // 情况2：一般字符匹配 
    if (isEqual(s[sbegin], p[pbegin])) 
        return recur(s, p, sbegin + 1, pbegin + 1); 
    
    return false;
}


bool isMatch(string s, string p) {
    return recur(s, p, 0, 0);
}

void addTestData(string& str, string& p) {
    str = "";
    p = "c*c*";
}

void showOutput(bool output) {
    cout << output << endl;
}

int main() {
    string str;
    string p;
    addTestData(str, p);
    showOutput(isMatch(str, p));
}
