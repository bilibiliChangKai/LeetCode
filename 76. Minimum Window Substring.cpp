#include <vector>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

/*
 * 用300长度的数组记录每个字符最后一次出现的index
 * 第一次循环求出第一个有效子串
 * 循环遍历剩下部分
 * 当出现新的字符与当前子串中最前的字符相同时，意味着出现了新的有效字串
 * 新的子串与当前储存的子串进行比较，取较短者
 */

// 寻找数组中最小值
int findMinCharIndex(int charLastIndex[]) {
  int index = 0;
  for (int i = 1; i < 300; i++)
    if (charLastIndex[i] < charLastIndex[index])  index = i;
  return index;
}

string minWindow(string s, string t) {
  int charLastIndex[300];         // 保存每个字符最后一次出现的位置
  int validHead;                 // 有效字符串的头字母
  int returnHeadPos;             // 返回字符串的首位置
  int returnLen;                 // 返回字符串的长度
  int sumAppearChar = 0;         // 出现过的有效的Char数量

  // 设置有效位
  for (int i = 0; i < 300; i++)
    charLastIndex[i] = s.length();
  for (int i = 0; i < t.length(); i++)
    charLastIndex[t[i]] = -1;

  int i;
  // 先找到最左边的有效字符串
  for (i = 0; i < s.length() && sumAppearChar != t.length(); i++) {
    // 无关字符处理
    if (charLastIndex[s[i]] == s.length())  continue;

    // 第一次出现
    if (charLastIndex[s[i]] == -1)
      sumAppearChar++;

    charLastIndex[s[i]] = i;
  }

  // 未找到有效字符串，返回""
  if (i == s.length() && sumAppearChar != t.length())  return "";

  // 第一个有效串
  validHead = findMinCharIndex(charLastIndex);
  returnHeadPos = charLastIndex[validHead];
  returnLen = i - returnHeadPos;

  for (; i < s.length(); i++) {
    // 无关字符处理
    if (charLastIndex[s[i]] == s.length())  continue;

    // 出现了新的头部字符，即出现了新的有效字符子串
    if (s[i] == validHead) {
      // cout << "Find:" << char('A' + validHead) << endl;
      charLastIndex[s[i]] = i;
      validHead = findMinCharIndex(charLastIndex);
      // cout << "ValidHead:" << char('A' + validHead) << endl;
      // cout << "Head:" << charLastIndex[validHead] << " i:" << i << endl;
      // for (int i = 0; i < 300; i++)  cout << charLastIndex[i] << ' ';
      // cout << endl;
      if (i + 1 - charLastIndex[validHead] < returnLen) {
        returnHeadPos = charLastIndex[validHead];
        returnLen = i + 1 - returnHeadPos;
      }
    } else {
      charLastIndex[s[i]] = i;
    }
  }

  return s.substr(returnHeadPos, returnLen);
}

 void addTestData(string &s, string &t) {
   s = "aa";
   t = "aa";
 }

 void outputData(string out) {
   cout << out << endl;
 }

 int main() {
  string str1, str2;
 addTestData(str1, str2);
 outputData(minWindow(str1, str2));
}
