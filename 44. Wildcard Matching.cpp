#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

bool isEqual(char a, char b) {
    return a == b || b == '?' || a == '?';
}

bool isEqual(string a, string b) {
    if (a.length() != b.length())  return false;
    for (int i = 0; i < a.length(); i ++)
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
