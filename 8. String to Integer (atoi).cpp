#include <iostream>
using namespace std;

// ԭ��: int atoi(const char *nptr);
// ����˵��: ����nptr�ַ����������һ���ǿո��ַ������ڻ���
// ��������Ҳ�����������򷵻��㣬����ʼ������ת����֮���
// �⵽������(���������� \0) �ַ�ʱֹͣת���������������� 

// �ӵ㣺
//   1.�ӵ�һ���ǿո��ַ���ʼ
//   2.�޷�Խ�磬ȡֵ��Χ������ 
//   3.����ʶ��"+123"֮������� 

int myAtoi(string str) {
    bool isNegative = false;     // ��ʾ����
    long long output = 0;     // ��ʾ���ֵ 
    
    // �������Ϊ��
    if (str.empty())  return output;
    
    // Ѱ�ҵ�һ���ո���ַ�λ�� 
    int i;
    for (i = 0; i < str.length(); i++)
        if (str[i] != ' ')  break;
    
    // û���ҵ�������0
    if (i == str.length())  return output;
    else if (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')  isNegative = true;
        i++;
    } 
    else if (!isdigit(str[i]))  return output;
    
    // �����ַ����
    while (i < str.length() && isdigit(str[i])) {
        output *= 10;
        output += str[i] - '0';
        i++;
        
        // �ж��Ƿ�Խ�� 
        if (output > 2147483648) {
            output = 2147483648;
            break;
        }
    }
    
    // ��������ţ�intȡֵ��ΧΪ-2^32----2^32-1 
    if (!isNegative) {
        if (output == 2147483648)  output--;
    }
    else  output = -output;
    
    return (int)output;
}

void addTestData(string& rows) {
    rows = "-2147483649";
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    string rows;
    addTestData(rows);
    showOutput(myAtoi(rows)); 
}
