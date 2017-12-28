#include "1007hza.h"
#include "1007hzl.h"

#include <iostream>
#include <vector>
using namespace std;

// 生成随机字符
char getRandomChar() {
  switch (rand() % 3) {
    case 0:
      return '0';
    case 1:
      return '+';
    case 2:
      return '-';
  }
}

// 相反char
char reserveChar(char ch) {
  if (ch == '0')  return '0';
  else if (ch == '+')  return '-';
  else  return '+';
}

// 生成随机矩阵
void RandomTestData(vector<vector<char>> &G, int n) {
  srand((unsigned)time(0));

  // 先生成data数组
  char data[n][n];
  for (size_t i = 0; i < n; i++)  data[i][i] = '0';
  // 随机生成右半部分
  for (size_t i = 0; i < n; i++)
    for (size_t j = i + 1; j < n; j++) {
      data[i][j] = getRandomChar();
      data[j][i] = reserveChar(data[i][j]);
    }

  G.clear();
  for (size_t i = 0; i < n; i++) {
    vector<char> temp;
    for (size_t j = 0; j < n; j++)
      temp.push_back(data[i][j]);
    G.push_back(temp);
  }
}

void showVectors(vector<vector<char>> &G) {
  cout << "\n测试数据如下：\n";
  for (int i = 0; i < G.size(); i++) {
    for (int j = 0; j < G.size(); j++)
      cout << G[i][j];
    cout << endl;
  }
}

int main(int argc, char const *argv[]) {
  Solution2 hza;
  Solution hzl;
  vector<vector<char>> G;
  for (int i = 0; i < 1000; i++) {
    RandomTestData(G, rand() % 51);
    int a = hza.minLeftMonsters(G);
    int b = hzl.minLeftMonsters(G);
    fprintf(stdout, "HZA: %d HZL: %d\n", a, b);
    if (a != b) {
      fprintf(stdout, "Test %d fail!\n", i + 1);
      showVectors(G);
      return 0;
    }
    fprintf(stdout, "Test %d success!\n", i + 1);
  }
  return 0;
}
