#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
//       int minDifference(vector<int> A) {
//             
//       }
};

int minDifference(vector<int> A) {
    sort(A.begin(), A.end());
    
    int minDif = A[1] - A[0];
    for (int i = 1; i < A.size() - 1; i++)
        if (A[i + 1] - A[i] < minDif)  minDif = A[i + 1] - A[i];
    
    return minDif;
}

void addTestData(vector<int> &A) {
    int data[100] = {2, 7, -2};
    int n = 3;
    for (int i = 0; i < n; i++)
        A.push_back(data[i]);
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    vector<int> test;
    addTestData(test);
    showOutput(minDifference(test)); 
}
