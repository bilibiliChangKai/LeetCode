#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * �ӵ�:
 * 1. �նԿ�
 * 2. �նԿ���ת���ɿյ��ַ�
 * 3. *��һ��Ҫƥ��������ͬ���ַ� 
 */ 

bool isEqual(char a, char b) {
    return a == b || b == '.';
}

// �ݹ���⣬ÿ��ֻ�ж�һ���ַ���isfirst�����ж��Ƿ����Ӵ�ƥ��ɹ��� 
bool recur(string &s, string &p, int sbegin, int pbegin) {
    // ���������sΪ�գ�����һ��ƥ��ɹ� 
    if (s.size() - sbegin == 0) {
        if (p.size() - pbegin == 0)  return true;
        else if (p.size() - pbegin >= 2 && p[pbegin + 1] == '*')
            return recur(s, p, sbegin, pbegin + 2);
        return false;
    }
    
    // ���������pΪ�գ�s��Ϊ�� 
    if (p.size() - pbegin == 0)  return false;
    
    // �ݹ����
    // ���1�������Ǻ� ���˴����õݹ飩 
    if (pbegin + 1 < p.size() && p[pbegin + 1] == '*') {
        // ���֮��������֮һ��ȫƥ�䣬����ȫƥ�� 
        int i;
        // ƥ��1-n����ͬ�ַ� 
        for (i = sbegin; i < s.size() && isEqual(s[i], p[pbegin]); i++)
            if (recur(s, p, i, pbegin + 2))  return true;
        // ƥ��������ͬ�ַ��������ַ���������ͬ 
        return recur(s, p, i, pbegin + 2); 
    }
    
    // ���2��һ���ַ�ƥ�� 
    if (isEqual(s[sbegin], p[pbegin])) 
        return recur(s, p, sbegin + 1, pbegin + 1); 
    
    return false;
}


bool isMatch(string s, string p) {
    return recur(s, p, 0, 0);
}

void addTestData(string& str, string& p) {
    str = "";
    p = "c*c*";
}

void showOutput(bool output) {
    cout << output << endl;
}

int main() {
    string str;
    string p;
    addTestData(str, p);
    showOutput(isMatch(str, p));
}
