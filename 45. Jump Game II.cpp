#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

/*
 * 坑点：
 * 1. 内存溢出
 * 2. 数组为[0]
 */

#define Step int
#define Index int

int jump(vector<int>& nums) {
  if (nums.size() == 1)  return 0;

  int n = nums.size();
  queue<pair<Index, Step>> que;   // BFS所用队列
  bool inQueue[n];  // 表示是否在队列里面
  for (int i = 0; i < n; i++)  inQueue[i] = false;

  // 起始位置step[0] = 0
  que.push(pair<Index, Step>(0, 0));
  inQueue[0] = true;

  // 进行BFS
  while (!que.empty()) {
    pair<Index, Step> temp = que.front();
    que.pop();

    for (int i = nums[temp.first]; i > 0; i--) {
      if (temp.first + i >= n - 1)  return temp.second + 1;
      if (!inQueue[temp.first + i]) {
        inQueue[temp.first + i] = true;
        que.push(pair<Index, Step>(temp.first + i, temp.second + 1));
      }
    }
  }

  return -1;
}

void addTestData(vector<int>& in) {
    int data[100] = {2,3,1,1,4};
    int n = 25000;
    for (size_t i = 0; i < n; i++)
      in.push_back(n - i);
    in.push_back(1);
    in.push_back(0);
}

void outputData(int output) {
    cout << output << endl;
}

int main() {
  vector<int> data;
  addTestData(data);
  outputData(jump(data));
}
