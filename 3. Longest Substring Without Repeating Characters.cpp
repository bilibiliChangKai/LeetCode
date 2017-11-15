#include <iostream>
#include <string>
using namespace std;

int lengthOfLongestSubstring(string s) {
    // 下标代表所有字符，储存的内容代表字符最后一次出现在string中的位置 
    int lastCharPos[300];
    for (int i = 0; i < 300; i++)
        lastCharPos[i] = -1;
    
    int begin = 0;                  // 子串的起始位置 
    int maxSubLength = 0;           // 子串的最大长度 
    int i;
    
    for (i = 0; i < s.size(); i++) {
        // 若第一次出现，记录位置 
        // 在子串初始位置前重复，无需更新长度 
        if (lastCharPos[s[i]] == -1 || lastCharPos[s[i]] < begin)
            lastCharPos[s[i]] = i;
        // 当前起始位置的子串已经不能匹配，需要换起始位置 
        else {
            // 更新长度 
            if (i - begin > maxSubLength)
                maxSubLength = i - begin;
            // 更新起始位置和数组相应数据 
            begin = lastCharPos[s[i]] + 1;
            lastCharPos[s[i]] = i;
        } 
    }
    
    // 计算匹配字符串末尾的子串长度 
    if (i - begin > maxSubLength)
        maxSubLength = i - begin;
        
    return maxSubLength; 
}

void addTestData(string& str) {
    str = "abba";
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    string str;
    addTestData(str);
    showOutput(lengthOfLongestSubstring(str)); 
}
