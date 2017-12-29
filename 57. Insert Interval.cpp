#include <vector>
#include <iostream>
using namespace std;

struct Interval {
   int start;
   int end;
   Interval() : start(0), end(0) {}
   Interval(int s, int e) : start(s), end(e) {}
};

// 寻找小于等于num但是最接近num的index
int findMaxLessThanNum(vector<Interval>& intervals, int num) {
  // 小于整个数组
  if (intervals[0].start > num)  return -1;

  for (int i = 1; i < intervals.size(); i++)
    if (intervals[i].start > num)  return i - 1;

  // 大于整个数组
  return intervals.size() - 1;
}

vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
  if (intervals.empty()) {
    intervals.push_back(newInterval);
    return intervals;
  }

  int startIndex = findMaxLessThanNum(intervals, newInterval.start);
  int endIndex = findMaxLessThanNum(intervals, newInterval.end);

  // 情况1: 在最前面
  if (endIndex == -1) {
    intervals.insert(intervals.begin(), newInterval);
    return intervals;
  }
  else if (startIndex == intervals.size() - 1) {
    // 情况2: 在最后面而且没有交集
    if (newInterval.start > intervals.back().end)
      intervals.push_back(newInterval);
    // 情况3: 在最后面而且有交集
    else {
      newInterval.start = intervals.back().start;
      newInterval.end = max(newInterval.end, intervals.back().end);
      intervals.erase(intervals.begin() + (intervals.size() - 1));
      intervals.push_back(newInterval);
    }
    return intervals;
  }

  // 修改start和startindex
  if (startIndex == -1 || newInterval.start > intervals[startIndex].end)
    startIndex++;
  else  newInterval.start = intervals[startIndex].start;

  // 修改endindex
  newInterval.end = max(newInterval.end, intervals[endIndex].end);

  // 删除冲突internal，添加新的internal
  intervals.erase(intervals.begin() + startIndex, intervals.begin() + (endIndex + 1));
  intervals.insert(intervals.begin() + startIndex, newInterval);

  return intervals;
}

void addTestData(vector<Interval> &in, Interval &newInterval) {
  int data[100] = {1,2,3,5,6,7,8,10,12,16};
  int len = 5;

  int nbegin = 4;
  int nend = 9;

  for (int i = 0; i < len; i++) {
    in.push_back(Interval(data[i * 2], data[i * 2 + 1]));
  }

  newInterval = Interval(nbegin, nend);
}

void outputData(vector<Interval> ins) {
    for (int i = 0; i < ins.size(); i++) {
      cout << "[" << ins[i].start << ", " << ins[i].end << "]" << endl;
    }
}

int main() {
  vector<Interval> matrix;
  Interval newIn;
  addTestData(matrix, newIn);
  outputData(insert(matrix, newIn));
}
