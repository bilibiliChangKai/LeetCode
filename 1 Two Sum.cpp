/*
 * �ӵ㣺1.�����и�ֵ
 *       2.����Ϊ0+0=0 
 */

#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    map<int, int> hashTable;        // ��map����hash�� 
    vector<int> returnVec;          // ���ڷ��ص�vector
    for (int i = 0; i < nums.size(); i++) {
        // ����Ӧֵ�����ڣ�����hash�� 
        if (hashTable.find(nums[i]) == hashTable.end())
            hashTable.insert(map<int, int>::value_type(target - nums[i], i));
        // ��Ӧֵ���ڣ�������
        else {
            
            int leftPosition = hashTable[nums[i]];
            // ��λ�÷��� 
            returnVec.push_back(leftPosition);
            returnVec.push_back(i);
            break;
        } 
    }
    return returnVec;
}

void addTestData(vector<int>& test, int& target) {
    target = 0;
    int data[100] = {-3,4,3,90};
    int n = 4;
    for (int i = 0; i < n; i++)
        test.push_back(data[i]);
}

void showOutput(vector<int> output) {
    cout << output[0] << " " << output[1] << endl;
}

int main() {
    vector<int> test;
    int target;
    addTestData(test, target);
    showOutput(twoSum(test, target)); 
}
