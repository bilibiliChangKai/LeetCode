#include <iostream>
#include <vector>
using namespace std;

int trap(vector<int>& height) {
    // sum - sumAir - sumBar = sumWater
    // sum = maxHeight * height.size()
    int sumBar = 0;
    int sumAir = 0;
    int maxHeight = 0;
    int maxHeightIndex = 0;
    
    // 除去左半部分Air 
    for (int i = 0; i < height.size(); i++) {
        // 更新bar总和 
        sumBar += height[i];
        // 更新Air总和 
        if (height[i] > maxHeight) {
            sumAir += i * (height[i] - maxHeight);
            // 记录最大值的下标 
            maxHeightIndex = i;
            maxHeight = height[i];
        }
    }
    
    maxHeight = 0;
    // 计算右半部分Air
    for (int i = height.size() - 1; i >= maxHeightIndex; i--) {
        if (height[i] > maxHeight) {
            sumAir += (height.size() - 1 - i) * (height[i] - maxHeight); 
            maxHeight = height[i];
        }
    } 
    
    return maxHeight * height.size() - sumAir - sumBar;
}

void addTestData(vector<int> &nums) {
    int data[100] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int n = 12;
    for (int i = 0; i < n; i++)
        nums.push_back(data[i]);
}

void outputData(int output) {
    cout << output << endl;
}

int main() {
    vector<int> test;
    addTestData(test);
    outputData(trap(test));
}
