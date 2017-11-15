#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

class Solution {
public:
//       vector<int> topologicalSort(int n, vector<pair<int, int>>& edges) {
//          
//    }
};

// DFS整张表 
void DFS(int nowPoint, int n, vector<int> *edgeTable, bool *enter, int *post) {
    // 第一次进入 
    enter[nowPoint] = true;
    
    vector<int> edge = edgeTable[nowPoint];
    for (int i = 0; i < edge.size(); i++) {
        // 已经被遍历过 
        if (enter[edge[i]]) {
            if (post[nowPoint] >= post[edge[i]])  post[nowPoint] = post[edge[i]] - 1;
            continue;
        }
        
        DFS(edge[i], n, edgeTable, enter, post);
        if (post[nowPoint] >= post[edge[i]])  post[nowPoint] = post[edge[i]] - 1;
    }
    
    // 已经遍历完毕，退出，如果是叶节点，修改post
    if (post[nowPoint] == n)
        post[nowPoint] = n - 1; 
}

vector<int> topologicalSort(int n, vector<pair<int, int>>& edges) {
    int time = 0;
    bool *enter = new bool[n];
    int *post = new int[n];
    for (int i = 0; i < n; i++) {
        enter[i] = false;
        post[i] = n;
    }
    
    // 处理边成线性表 
    vector<int> edgeTable[n];
    for (int i = 0; i < edges.size(); i++)
        edgeTable[edges[i].first].push_back(edges[i].second);
    
    // 递归 
    for (int i = 0; i < n; i++)
        if (!enter[i])  DFS(i, n, edgeTable, enter, post);
    
    // 对顺序进行排序 
    vector<pair<int, int>> sortArr;
    for (int i = 0; i < n; i++)
        sortArr.push_back(pair<int, int>(post[i], i));
    sort(sortArr.begin(), sortArr.end()); 
    
    vector<int> returnArr;
    for (int i = 0; i < n; i++)
        returnArr.push_back(sortArr[i].second);

    return returnArr;
}

void addTestData(int &n, vector<pair<int, int>>& A) {
    n = 8;
    
    int edge[1000] = {5,1, 5,2};
    int edges = 2;
    for (int i = 0; i < edges; i++) {
        pair<int, int> temp = pair<int, int>(edge[i * 2], edge[i * 2 + 1]);
        A.push_back(temp);
    }
}

void showOutput(vector<int> A) {
    for (int i = 0; i < A.size(); i++)
        cout << A[i] << " ";
}

int main() {
    int n;
    vector<pair<int, int>> edge;
    addTestData(n, edge);
    showOutput(topologicalSort(n, edge)); 
}
