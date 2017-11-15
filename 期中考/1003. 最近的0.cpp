#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
//    vector<vector<int>> nearestZero(vector<vector<int>>& A) {
//                        
//    }
};

// �����ݽṹ 
struct Point {
    int x;
    int y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// �����ĸ����� 
int Posx[4] = {-1, 0, 1, 0};
int Posy[4] = {0, -1, 0, 1};

bool isValid(int x, int y, vector<vector<int>>& A) {
    return x >= 0 && x < A.size() &&
        y >= 0 && y < A[x].size();
}

vector<vector<int>> nearestZero(vector<vector<int>>& A) {
    queue<Point> q1, q2;        // ��������ͬ�ڵ��ջ
    int step = 1;               // ��ʾ�ߵ�0����Ĳ���������һ��ջ��һ��ֵ 
    
    // ��1���³�-1����δ��ֵ����0��ջ 
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < A[i].size(); j++)
            if (A[i][j] == 0)  q1.push(Point(i, j));
            else  A[i][j] = -1;
    
    while (!q1.empty() || !q2.empty()) {
        while (!q1.empty()) {
            Point p = q1.front();
            q1.pop();
            // ����ĸ�����Ľڵ� 
            for (int i = 0; i < 4; i++) {
                int newx = p.x + Posx[i];
                int newy = p.y + Posy[i];
                if (isValid(newx, newy, A) && A[newx][newy] == -1) {
                    A[newx][newy] = step;
                    q2.push(Point(newx, newy));
                }
            }
        }
        step++;
        
        while (!q2.empty()) {
            Point p = q2.front();
            q2.pop();
            // ����ĸ�����Ľڵ� 
            for (int i = 0; i < 4; i++) {
                int newx = p.x + Posx[i];
                int newy = p.y + Posy[i];
                if (isValid(newx, newy, A) && A[newx][newy] == -1) {
                    A[newx][newy] = step;
                    q1.push(Point(newx, newy));
                }
            }
        }
        step++;
    }
    
    return A;
}



void addTestData(vector<vector<int>>& A) {
    int data[1000] = {1,1,1,
                     0,1,1,
                     0,0,1};
    int x = 3, y = 3;
    for (int i = 0; i < x; i++) {
        vector<int> temp;
        for (int j = 0; j < y; j++)
            temp.push_back(data[i * y + j]);
        A.push_back(temp);
    }
}

void showOutput(vector<vector<int>> A) {
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            cout << A[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> test;
    addTestData(test);
    showOutput(nearestZero(test)); 
}
