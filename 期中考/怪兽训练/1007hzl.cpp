#include <vector>
#include <iostream>
using namespace std;

class Solution {
  static const int M = 51;
int Index=0;//索引号
int STACK[M],top=0;//Tarjan算法中的栈
bool InStack[M];//检查是否在栈中
int DFN[M];//深度优先搜索访问次序
int Low[M];//能追溯到的最早的次序
int ComponentNumber=0;//有向图强连通分量个数
vector<int> Edge[M];//邻接表表示
vector<int> Component[M];//获得强连通分量结果
int InComponent[M];//记录每个点在第几号强连通分量里
public:
	void Tarjan(int i){
    	int j;
    	DFN[i]=Low[i]=Index++;
    	InStack[i]=true;STACK[++top]=i;
    	for (int e=0;e<Edge[i].size();e++)
    	{
        	j=Edge[i][e];
        	if (DFN[j]==-1)
        	{
            	Tarjan(j);
            	Low[i]=min(Low[i],Low[j]);
        	}
        	else
            	if (InStack[j]) Low[i]=min(Low[i],DFN[j]);
    	}
    	if (DFN[i]==Low[i])
    	{

        	do{
            	j=STACK[top--];
            	InStack[j]=false;
            	Component[ComponentNumber].push_back(j);
            	InComponent[j]=ComponentNumber;
        	}
        	while (j!=i);
        	ComponentNumber++;
    	}
	}
    int minLeftMonsters(vector<vector<char> > G){
    	int ans = 0;
    	int m = G.size(), n = G[0].size();
    	top=0;
    	ComponentNumber=0;
    	for(int i = 0; i < m; i++){
    		DFN[i] = -1;
    		Low[i] = -1;
    		Edge[i].clear();
    		Component[i].clear();
    		InStack[i] = false;
    		for(int j = 0; j < n; j++){
    			if(G[i][j] == '+'){
    				Edge[i].push_back(j);
				}
			}
		}
		for(int i = 0; i < m; i++){
    		if (DFN[i] == -1)
            	Tarjan(i);
		}
		for(int i = 0; i < ComponentNumber; i++){
    		int size = Component[i].size();
    		bool t = true;
    		for(int j = 0; j < size; j++){
    			t = false;
    			for (int e=0;e<Edge[Component[i][j]].size();e++){
    				if(InComponent[Edge[Component[i][j]][e]] != i){
    					t = true;
    					break;
					}
				}
				if(t) break;
			}
			if(t == false){
				ans++;
			}
		}
		return ans;
	}
};
// int main(){
// 	vector<vector<char> > G;
// 	for(int i = 0; i < 3; i++){
// 		vector<char> row;
// 		for(int j = 0; j < 3; j++){
// 			char c;
// 			cin >> c;
// 			row.push_back(c);
// 		}
// 		G.push_back(row);
// 	}
// 	Solution s;
// 	cout << s.minLeftMonsters(G);
// }
