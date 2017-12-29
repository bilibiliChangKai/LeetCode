#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

/*
 * 经典动态规划问题
 *
 */



// 动态规划函数
int findDistance(vector<vector<int>>& dp, int i, int j, string& word1, string& word2) {
  // 第一次进入
  if (dp[i][j] == -1) {
    if (word1[i - 1] == word2[j - 1])
      dp[i][j] = findDistance(dp, i - 1, j - 1, word1, word2);
    else
      dp[i][j] = min(min(findDistance(dp, i - 1, j, word1, word2)
        , findDistance(dp, i, j - 1, word1, word2))
        , findDistance(dp, i - 1, j - 1, word1, word2)) + 1;
  }

  return dp[i][j];
}

int minDistance(string word1, string word2) {
  vector<vector<int>> dp;  // 用于保存结果的动态规划数组
  // 初始化数组
  for (int i = 0; i <= word1.length(); i++) {
    vector<int> temp;
    for (int j = 0; j <= word2.length(); j++)
      temp.push_back(-1);
    dp.push_back(temp);
  }

  // 初始化条件
  dp[0][0] = 0;
  for (int i = 1; i <= word1.length(); i++)   dp[i][0] = i;
  for (int i = 1; i <= word2.length(); i++)   dp[0][i] = i;

  int ans = findDistance(dp, word1.length(), word2.length(), word1, word2);

  return ans;
}

void addTestData(string &word1, string &word2) {
  word1 = "algorithm";
  word2 = "altruistic";
}

void outputData(int out) {
  cout << out << endl;
}

int main() {
  string str1, str2;
  addTestData(str1, str2);
  outputData(minDistance(str1, str2));
}
