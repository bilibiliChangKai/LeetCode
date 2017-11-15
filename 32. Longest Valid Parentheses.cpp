#include <iostream>
#include <stack>
using namespace std;

// ��ջ��� 

int longestValidParentheses(string s) {
    int longestLength = 0;                // ���������
    int validStringEnd;                   // ��¼��Ч�ַ������յ㣬���ڱ���ջ 
    stack<pair<char, int>> sta;           // ����ƥ��()��ջ����һ��intֵ��¼�÷������ַ���s�е�λ�� 
    
    for (int i = 0; i < s.length(); i++) {
        // ���Ϊ'('����ջ 
        if (s[i] == '(') {
            pair<char, int> p('(', i);
            sta.push(p);
        }
        // ���Ϊ')'
        else {
            // �ж�ջ���Ƿ�Ϊ'('������ǣ���ջ��ͬʱ��Ϊ����һ��()ƥ��
            if (!sta.empty() && sta.top().first == '(')
                sta.pop();
            // ���ǣ����ַ���δƥ�䣬�Ӵ�ƥ����� 
            else {
                pair<char, int> p(')', i);
                sta.push(p);
            }
        }
    } 
    
    // ���ջ��ʣ�µľ����޷�ƥ��Ĳ��֣����Ի����Щ�ַ���s�е�λ��
    // ջ�׵�λ��ǰ��ջ����λ�ú󣬰�˳������ 
    // �������ڵ�λ��֮�����һ����Ч�ַ���
     
    validStringEnd = s.length();
    // ���α�����Щ�ַ����ĳ��ȣ��õ����ֵ 
    while (!sta.empty()) {
        pair<char, int> p = sta.top();
        sta.pop();
        if (validStringEnd - p.second - 1 > longestLength)
            longestLength = validStringEnd - p.second - 1;
        validStringEnd = p.second;
    }
    
    // ��ͷƥ�� 
    if (validStringEnd - 0 > longestLength)
        longestLength = validStringEnd - 0;
    
    return longestLength;
}

void addTestData(string &s) {
    s = ")";
}

void outputData(int data) {
    cout << data << endl;
}

int main() {
    string s;
    addTestData(s);
    outputData(longestValidParentheses(s));
} 
