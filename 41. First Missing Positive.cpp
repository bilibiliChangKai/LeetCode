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
    int target = -1;                       // ȡ����ֵΪ-1�����nums[i]=-1������ԭ�����д���ֵ(i+1)
    
    // ��һ�α������飬������ֵ��ȥ 
    for (int i = 0; i < nums.size(); i++)
        if (nums[i] == -1)  nums[i] = 0;
        
    // �ڶ��α������飬�ݹ���������ֵ����������Ϊֹ 
    for (int i = 0; i < nums.size(); i++) {
        int value = nums[i];
        while (value > 0 && value <= nums.size()) {
            int nowPos = value - 1;
            value = nums[value - 1];
            nums[nowPos] = -1;
        }
    }
    
    // �����α������飬�ҵ�����ֵ-1�ĵ�һ��nums[i]����
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
