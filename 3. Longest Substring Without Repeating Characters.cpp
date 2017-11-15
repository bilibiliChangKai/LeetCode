#include <iostream>
#include <string>
using namespace std;

int lengthOfLongestSubstring(string s) {
    // �±���������ַ�����������ݴ����ַ����һ�γ�����string�е�λ�� 
    int lastCharPos[300];
    for (int i = 0; i < 300; i++)
        lastCharPos[i] = -1;
    
    int begin = 0;                  // �Ӵ�����ʼλ�� 
    int maxSubLength = 0;           // �Ӵ�����󳤶� 
    int i;
    
    for (i = 0; i < s.size(); i++) {
        // ����һ�γ��֣���¼λ�� 
        // ���Ӵ���ʼλ��ǰ�ظ���������³��� 
        if (lastCharPos[s[i]] == -1 || lastCharPos[s[i]] < begin)
            lastCharPos[s[i]] = i;
        // ��ǰ��ʼλ�õ��Ӵ��Ѿ�����ƥ�䣬��Ҫ����ʼλ�� 
        else {
            // ���³��� 
            if (i - begin > maxSubLength)
                maxSubLength = i - begin;
            // ������ʼλ�ú�������Ӧ���� 
            begin = lastCharPos[s[i]] + 1;
            lastCharPos[s[i]] = i;
        } 
    }
    
    // ����ƥ���ַ���ĩβ���Ӵ����� 
    if (i - begin > maxSubLength)
        maxSubLength = i - begin;
        
    return maxSubLength; 
}

void addTestData(string& str) {
    str = "abba";
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    string str;
    addTestData(str);
    showOutput(lengthOfLongestSubstring(str)); 
}
