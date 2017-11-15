#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
//       int minPartition(vector<int> A, int w) {
//             
//       }
}; 

int minPartition(vector<int> A, int w) {
    // ÅÅÐòA 
    sort(A.begin(), A.end());
    
    int i = A.size() - 1, j = 0, sumNum = 0;
    while (i >= j) {
        if (A[i] + A[j] <= w)  j++;
        i--;
        sumNum++;
    }
    
    return sumNum;
}

void addTestData(vector<int> &A, int &w) {
    int data[100] = {2, 5, 4, 3};
    int n = 4;
    for (int i = 0; i < n; i++)
        A.push_back(data[i]);
    w = 7;
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    vector<int> test;
    int target;
    addTestData(test, target);
    showOutput(minPartition(test, target)); 
}
