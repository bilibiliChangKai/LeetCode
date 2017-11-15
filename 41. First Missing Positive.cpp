#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*int firstMissingPositive(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    
    int i;
    int returnNum = 1;
    for (i = 0; i < nums.size(); i++)
        if (nums[i] > 0)  break;
    
    for (; i < nums.size(); i++)
        if (nums[i] > returnNum)  break;
        else if (nums[i] == returnNum)  returnNum++;
    
    return returnNum;
}*/

int firstMissingPositive(vector<int>& nums) {
    int target = -1;                       // 取特征值为-1，如果nums[i]=-1，代表原数组中存在值(i+1)
    
    // 第一次遍历数组，将特征值消去 
    for (int i = 0; i < nums.size(); i++)
        if (nums[i] == -1)  nums[i] = 0;
        
    // 第二次遍历数组，递归设置特征值至不能设置为止 
    for (int i = 0; i < nums.size(); i++) {
        int value = nums[i];
        while (value > 0 && value <= nums.size()) {
            int nowPos = value - 1;
            value = nums[value - 1];
            nums[nowPos] = -1;
        }
    }
    
    // 第三次遍历数组，找到不是值-1的第一个nums[i]即可
    for (int i = 0; i < nums.size(); i++)
        if (nums[i] != -1)  return i + 1;
    return nums.size() + 1; 
}

void addTestData(vector<int> &nums) {
    int data[100] = {0,2,2,1,1};
    int n = 5;
    for (int i = 0; i < n; i++)
        nums.push_back(data[i]);
}

void outputData(int output) {
    cout << output << endl;
}

int main() {
    vector<int> test;
    addTestData(test);
    outputData(firstMissingPositive(test));
}
