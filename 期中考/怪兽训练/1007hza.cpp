#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
  解决方法:
    1.将狩猎顺序看成一幅图
    2.对点先根据联通块进行分组,每个组最少有一个怪兽存活
    3.观察每组的源点,如果存在多个,则有多个怪兽存货
 */

class Solution2 {
public:
// DFS填写post
void DFS(int node, vector<vector<char>> &edges, bool* isVisit, int* post, int &nowPost) {
  // 加锁
  isVisit[node] = true;

  // 访问所有节点
  for (size_t j = 0; j < edges.size(); j++)
    if (edges[node][j] == '-' && !isVisit[j])  DFS(j, edges, isVisit, post, nowPost);

  // 添加POST值
  post[node] = nowPost++;
}

int minLeftMonsters(vector<vector<char>> G) {
  bool isVisit[100];  // 判断有无被访问
  int post[100];  // 节点post值
  int nowPost = 0;  // 当前post值，使用过后++
  int sortArr[100];  // 排序post的数组
  int minLeftNum = 0;  // 最后剩下的怪兽数量
  for (size_t i = 0; i < 100; i++) {
    isVisit[i] = false;
    post[i] = 0;
  }

  // 构建post数组
  for (int i = G.size() - 1; i >= 0; i--) {
    if (!isVisit[i])  DFS(i, G, isVisit, post, nowPost);
  }

  // 将值和下标互换
  for (size_t i = 0; i < G.size(); i++)
    sortArr[post[i]] = i;

  // 根据post由大到小做DFS
  memset(isVisit, false, sizeof(isVisit));
  for (int i = G.size() - 1; i >= 0; i--) {
    if (!isVisit[sortArr[i]]) {
      minLeftNum++;
      DFS(sortArr[i], G, isVisit, post, nowPost);
    }
  }
  return minLeftNum;
}
};

void addTestData(vector<vector<char>> &G) {
	string data[10000] = {
"0++--0+-+-0-+++0+-00+-00+--00-+-0",
"-0--00+0-0+-00+0+++-0+0+00+0+0-+-",
"-+0-+-0-000+-0+++00+++-+-0-+0+0+-",
"+++0-00-0-0+0-0++-+---0+--+-+-000",
"+0-+0+0--000+0+-0-0-----+0+000000",
"00+0-0-0+0++00+++-0+0-------0++-+",
"--000+0+0++-00++--+00000+++++00+-",
"+0+++0-0+0+++--+----00--0000++---",
"-+00+-0-0+00--00--0--0+--000+-0+-",
"+00+00-0-0+-+0-0-+-00-+00++0+++++",
"0-000---0-0++-0+--++-0-+-+-+00++0",
"++--0-+-0+-0-0--+0+0-0-+++-00+-00",
"-0+0-00-+--+0+--++-+++-0--++0--00",
"-00+000++0+0-0--++-+-0+-+-00+-0-0",
"---0---+0+0+++0-+--+0+--00-0-+--0",
"00--+---00-++++0+-+-++---+0-0---+",
"----0-+++++-----0+-00-+00-++-0-++",
"+-0++++++-+0--++-0+0-0--0--000---",
"0-0-00-+0+--+++-+-00-0+----++-+0+",
"0+-++-0++0-0---+00000-0++0---++--",
"-0-++000+0++-+0-0++00--+-0+--0++0",
"+--+++000+00-0--+00++0000-0+00++-",
"00+0++0+--+++-++-+-0+0000+--+-+0-",
"0---++0++0--0+++0++--0000-0-+-0-+",
"-0++-+-0+0+-+-0+00+-+0000++++0-0+",
"+00+0+-00---++0-+++00+-+-0----0++",
"+-+--+-00-++-0+0-+++-0+0-+00+--+0",
"00-+0+-000-0-00+-0-++-++-+00-----",
"0-0-00----000-+0+0-++0---+-+0--0-",
"+0-+0-0-+-0-++-+00+-00++0++++0++0",
"-+000-0+0--++0++++-----0+0+++-0-0",
"+--00+-+---00+++-+0+--0+0--+0-+0+",
"0++00-+++-00000--+-+0++---0++00-0"
	};
	int n = 33;

	G.clear();
	for (size_t i = 0; i < n; i++) {
		vector<char> temp;
		for (size_t j = 0; j < n; j++) {
			temp.push_back(data[i][j]);
		}
		G.push_back(temp);
	}
}

void outputData(int n) {
	cout << n << endl;
}

int main() {
	Solution2 hza;
	vector<vector<char>> G;
	addTestData(G);
	int out = hza.minLeftMonsters(G);
	outputData(out);
}
