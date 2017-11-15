#include <iostream>
#include <string>
using namespace std;

string longestPalindrome(string s) {
    string maxPalString;         // 返回的最大回文字符串
    int length = s.size();       // 输入字符串的长度 
    if (!s.empty())  maxPalString = s.substr(0, 1);  // 默认为单个字符 
    
    int j;                       // 用于遍历 
    int left;                    // 左边字符的位置
    int right;                   // 右边字符的位置
     
    // 将两个字符中间的空位也看成一个字符，每个字符作为回文串的中间值，
    // 因此:
    //      长length的字符串长度变成了2*length-1，去掉首尾字母，即1->2*length-3 
    for (int i = 1; i < 2 * length - 2; i++) {
        j = 1;
        // 偶数，即为真正的字符 
        if (i % 2 == 0) {
            // 不停将左右两边的字符进行比较，最后得出的就是该位置为中值的最大子串 
            while (1) {
                left = i / 2 - j;
                right = i / 2 + j;
                // 两种越界情况 
                if (left < 0)  break;
                if (right >= length)  break;
                // 左右值不匹配，跳出 
                if (s[left] != s[right])  break;
                j++;
            }
        } 
        // 奇数，即空白 
        else {
            // 不停将左右两边的字符进行比较，最后得出的就是该位置为中值的最大子串
            while (1) {
                left = (i + 1) / 2 - j;
                right = i / 2 + j;
                // 两种越界情况
                if (left < 0)  break;
                if (right >= length)  break;
                // 左右值不匹配，跳出 
                if (s[left] != s[right])  break;
                j++;
            }
        }
        
        // 如果该子串较大，赋值 
        if (right - left - 1 > maxPalString.size())
            maxPalString = s.substr(left + 1, right - left - 1);   
    }
    
    return maxPalString; 
}

void addTestData(string& str) {
    str = "cbbd";
}

void showOutput(string output) {
    cout << output << endl;
}

int main() {
    string str;
    addTestData(str);
    showOutput(longestPalindrome(str)); 
}
