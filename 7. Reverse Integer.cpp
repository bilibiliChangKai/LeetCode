#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int reverse(int x) {
    bool isNegative = x < 0;      // �ж�����
    x = abs(x);

    char contain[100];            // ��Ϊ��תվ
    sprintf(contain, "%d", x);

    // �ַ�����ת
    int length;
    for (int i = 0; i < 100; i++)
        if (contain[i] == '\0') {
            length = i;
            break;
        }
    for (int i = 0; i < length / 2; i++) {
        char temp = contain[i];
        contain[i] = contain[length - i - 1];
        contain[length - i - 1] = temp;
    }

    long output;          // ���ڻᳬ��2^31-1����long�Ƚ�
    sscanf(contain, "%ld", &output);

    // ������������
    if (isNegative)  output = -output;

    // �ж��Ƿ�Խ��
    if (output > pow(2, 31) - 1 || output < -pow(2, 31))  output = 0;

    return (int)output;
}

void addTestData(int& rows) {
    rows = -12345679;
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    int rows;
    addTestData(rows);
    showOutput(reverse(rows));
}
