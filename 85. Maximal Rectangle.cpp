#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
#include <stack>
using namespace std;

/*
 * 思路：
 * 将每条横看成一个直方图
 * 缺点：
 * 无
 *
 */

struct Matrix {
  int left;
  int index;
  int height;

  Matrix(int l, int i, int h) : left(l), index(i), height(h) {
  }
};

// 84 题目
int largestRectangleArea(vector<int>& heights) {
  if (heights.size() == 0)  return 0;

  stack<Matrix> sta;  // 用于计算的栈
  int maxSize = 0;            // 保存最大值
  int n = heights.size();     // size

  for (int i = 0; i < n; i++) {
    // 空栈，直接push
    if (sta.empty())  sta.push(Matrix(0, i, heights[i]));
    // 当高过栈顶时，直接push
    if (heights[i] >= sta.top().height)
      sta.push(Matrix(i, i, heights[i]));
    // 当低过栈顶时。计算栈顶，弹出，直到高过栈顶
    else {
      do {
        maxSize = max(maxSize, (i - sta.top().left) * sta.top().height);
        sta.pop();
      } while(!sta.empty() && heights[i] < sta.top().height);
      if (sta.empty())  sta.push(Matrix(0, i, heights[i]));
      else  sta.push(Matrix(sta.top().index + 1, i, heights[i]));
    }
  }

  // 清楚剩余空间
  while (!sta.empty()) {
    maxSize = max(maxSize, (n - sta.top().left) * sta.top().height);
    sta.pop();
  }

  return maxSize;
}

// 生成直方图集合
vector<vector<int>> geneHistograms(vector<vector<char>>& matrix) {
  vector<vector<int>> histograms;

  // 插入第一行
  if (!matrix.empty()) {
    vector<int> temp;
    for (int j = 0; j < matrix[0].size(); j++)
      temp.push_back(matrix[0][j] - '0');
    histograms.push_back(temp);
  }

  // 插入之后的行
  for (int i = 1; i < matrix.size(); i++) {
    vector<int> temp;
    for (int j = 0; j < matrix[0].size(); j++)
      if (matrix[i][j] == '0')  temp.push_back(0);
      else  temp.push_back(histograms[i - 1][j] + 1);
    histograms.push_back(temp);
  }

  return histograms;
}

int maximalRectangle(vector<vector<char>>& matrix) {
  vector<vector<int>> histograms;       // 直方图集合
  int maxSize = 0;                      // 最大值
  histograms = geneHistograms(matrix);

  // for (int i = 0; i < histograms.size(); i++) {
  //   for (int j = 0; j < histograms[i].size(); j++) {
  //     cout << histograms[i][j];
  //   }
  //   cout << endl;
  // }

  // 将每条看成一个直方图
  for (int i = 0; i < histograms.size(); i++)
    maxSize = max(maxSize, largestRectangleArea(histograms[i]));

  return maxSize;
}

void addTestData(vector<vector<char>> &in) {
  string data[100] = {
    "10100",
    "10111",
    "11111",
    "10010"
  };

  int xlen = 4;

  for (int i = 0; i < xlen; i++) {
    vector<char> temp;
    for (int j = 0; j < data[i].size(); j++)
      temp.push_back(data[i][j]);
    in.push_back(temp);
  }
}

void outputData(int output) {
    cout << output << endl;
}

int main() {
  vector<vector<char>> matrix;
  addTestData(matrix);
  outputData(maximalRectangle(matrix));
}
