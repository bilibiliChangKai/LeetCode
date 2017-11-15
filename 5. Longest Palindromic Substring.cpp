#include <iostream>
#include <string>
using namespace std;

string longestPalindrome(string s) {
    string maxPalString;         // ���ص��������ַ���
    int length = s.size();       // �����ַ����ĳ��� 
    if (!s.empty())  maxPalString = s.substr(0, 1);  // Ĭ��Ϊ�����ַ� 
    
    int j;                       // ���ڱ��� 
    int left;                    // ����ַ���λ��
    int right;                   // �ұ��ַ���λ��
     
    // �������ַ��м�Ŀ�λҲ����һ���ַ���ÿ���ַ���Ϊ���Ĵ����м�ֵ��
    // ���:
    //      ��length���ַ������ȱ����2*length-1��ȥ����β��ĸ����1->2*length-3 
    for (int i = 1; i < 2 * length - 2; i++) {
        j = 1;
        // ż������Ϊ�������ַ� 
        if (i % 2 == 0) {
            // ��ͣ���������ߵ��ַ����бȽϣ����ó��ľ��Ǹ�λ��Ϊ��ֵ������Ӵ� 
            while (1) {
                left = i / 2 - j;
                right = i / 2 + j;
                // ����Խ����� 
                if (left < 0)  break;
                if (right >= length)  break;
                // ����ֵ��ƥ�䣬���� 
                if (s[left] != s[right])  break;
                j++;
            }
        } 
        // ���������հ� 
        else {
            // ��ͣ���������ߵ��ַ����бȽϣ����ó��ľ��Ǹ�λ��Ϊ��ֵ������Ӵ�
            while (1) {
                left = (i + 1) / 2 - j;
                right = i / 2 + j;
                // ����Խ�����
                if (left < 0)  break;
                if (right >= length)  break;
                // ����ֵ��ƥ�䣬���� 
                if (s[left] != s[right])  break;
                j++;
            }
        }
        
        // ������Ӵ��ϴ󣬸�ֵ 
        if (right - left - 1 > maxPalString.size())
            maxPalString = s.substr(left + 1, right - left - 1);   
    }
    
    return maxPalString; 
}

void addTestData(string& str) {
    str = "cbbd";
}

void showOutput(string output) {
    cout << output << endl;
}

int main() {
    string str;
    addTestData(str);
    showOutput(longestPalindrome(str)); 
}
