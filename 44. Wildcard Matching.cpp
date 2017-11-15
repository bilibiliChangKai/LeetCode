#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
/*
// ����s�ĵ�iλ֮����Ӵ�����p�ĵ�jλ֮����Ӵ�ƥ��Ľ�� 
int ijEqual[100][100];

// �ݹ���⣬ÿ��ֻ�ж�һ���ַ�
bool recur(string &s, string &p, int sbegin, int pbegin) {
    // ���������sΪ�գ�����һ��ƥ��ɹ� 
    if (s.size() - sbegin == 0) {
        if (p.size() - pbegin == 0)  return true;
        // ���p�Ƿ�ֻ��* 
        for (int i = pbegin; i < p.length(); i++)
            if (p[i] != '*')  return false;
        return true;
    }
    
    // ���������pΪ�գ�s��Ϊ�� 
    if (p.size() - pbegin == 0)  return false;
    
    // �ݹ����
    // ���1�������Ǻ� 
    if (p[pbegin] == '*') {
        // ���֮��������֮һ��ȫƥ�䣬����ȫƥ�� 
        // ƥ��1-n���ַ� 
        for (int i = sbegin; i <= s.size(); i++) {
            // ���˶���* 
            int j;
            for (j = pbegin + 1; j < p.length() && p[j] == '*'; j++)
            
            if (ijEqual[i][pbegin] == -1)
                ijEqual[i][pbegin] = recur(s, p, i, j - 1);
            if (ijEqual[i][pbegin] == 1)  return true;
        }
        return false;
    }
    
    // ���2��һ���ַ�ƥ�� 
    if (isEqual(s[sbegin], p[pbegin])) {
        if (ijEqual[sbegin][pbegin] == -1)
            ijEqual[sbegin][pbegin] = recur(s, p, sbegin + 1, pbegin + 1);
        return ijEqual[sbegin][pbegin];
    }
    
    
    return false;
}
*/

bool isEqual(char a, char b) {
    return a == b || b == '?' || a == '?';
}

bool isEqual(string a, string b) {
    if (a.length() != b.length())  return false;
    for (int i = 0; i < a.length(); i++)
        if (!isEqual(a[i], b[i]))  return false;
    return true;
}

int subStr(string s, string b, int pos = 0) {
    for (int j = pos; j <= int(s.size() - b.size()); j++) {
        int k;
        for (k = 0; k < b.length(); k++)
            if (!isEqual(b[k], s[j + k]))  break;
        if (k == b.length())  return j; 
    }
    return -1;
}

// �и��ַ��� 
vector<string> split(string& str,const char* c)
{
    char *cstr, *p;
    vector<string> res;
    cstr = new char[str.size()+1];
    strcpy(cstr,str.c_str());
    p = strtok(cstr,c);
    while(p!=NULL)
    {
        res.push_back(p);
        p = strtok(NULL,c);
    }
    return res;
}

bool isMatch(string s, string p) {
    // û��*����� 
    if (p.find('*') == -1)  return isEqual(s, p);
    
    vector<string> splitStrs = split(p, "*");  // ���ַ�������*�ָ� 
    
    // ��һ���̶���û��*
    if (p[0] != '*') {
        string firstStr = splitStrs.front();
        splitStrs.erase(splitStrs.begin());
        
        // �ж�ͷ���Ƿ���� 
        if (s.length() < firstStr.length() ||
            !isEqual(s.substr(0, firstStr.length()), firstStr))  return false;    
        s.erase(0, firstStr.length());
    }     
    
    // ���һ���̶���û��* 
    if (p[p.length() - 1] != '*') {
        string endStr = splitStrs.back();
        splitStrs.pop_back();
        
        // �ж�β���Ƿ���� 
        if (s.length() < endStr.length() ||
            !isEqual(s.substr(s.length() - endStr.length(), endStr.length()), endStr))  return false;    
        s.erase(s.length() - endStr.length(), endStr.length());
    }
    
    int pos = 0;
    for (int i = 0; i < splitStrs.size(); i++) {
        // ����̰�ģ�Ѱ�ҵ�һ���Ӵ�
        pos = subStr(s, splitStrs[i], pos);
        
        // ���֮�󲻴����Ӵ�ƥ�䣬ֱ���˳� 
        if (pos == -1)  return false;
        pos += splitStrs[i].length();
    }
    return true; 
}

void addTestData(string &s, string &p) {
    s = "aaab";
    p = "b**";
}

void outputData(bool output) {
    cout << output << endl;
}

int main() {
    string s, p;
    addTestData(s, p);
    //vector<string> newVec = split(p, "*");
    //for (int i = 0; i < newVec.size(); i++)
        //cout << newVec[i] << endl;
    outputData(isMatch(s, p));
}
