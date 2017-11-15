#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
//    int minSum(vector<int>& A) {
//          
//    }
};

int minSum(vector<int>& A) {
    // 特殊情况 
    if (A.size() == 1)  return A[0];
    else if (A.size() == 2)  return min(A[0], A[1]);
    
    // 用于储存地推序列结果的数组 
    int *S = new int[A.size()];
    
    S[0] = min(A[0], A[1]);
    S[1] = min(A[2] + S[0], A[1] + 0); // S[-1] = 0
    
    // 递推式：
    // S[n] = min{ A[n + 1] + S[n - 1], A[n] + S[n - 2] } 
    for (int i = 2; i < A.size() - 1; i++)
        S[i] = min(A[i + 1] + S[i - 1], A[i] + S[i - 2]);
    
    return S[A.size() - 2];
}

void addTestData(vector<int> &A) {
    int data[100] = {2, 5, 2, 3, 9, 6, 8, 0};
    int n = 8;
    for (int i = 0; i < n; i++)
        A.push_back(data[i]);
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    vector<int> test;
    addTestData(test);
    showOutput(minSum(test)); 
}
