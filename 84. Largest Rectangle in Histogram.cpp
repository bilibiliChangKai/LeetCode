#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <stack>
using namespace std;

/*
 * 缺点：
 * =要考虑
 * 弹出时要单独考虑
 *
 */

struct Matrix {
  int left;
  int index;
  int height;

  Matrix(int l, int i, int h) : left(l), index(i), height(h) {
  }
};

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

void addTestData(vector<int> &in) {
  int data[100] = {3,2,8,9,1,0,0,8,6,4,8,0,7,9,5};

  int len = 15;

  for (int i = 0; i < len; i++) {
    in.push_back(data[i]);
  }
}

void outputData(int output) {
    cout << output << endl;
}

int main() {
  vector<int> matrix;
  addTestData(matrix);
  outputData(largestRectangleArea(matrix));
}
