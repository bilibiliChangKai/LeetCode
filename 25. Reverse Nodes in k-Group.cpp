#include <iostream>
#include <stack>
using namespace std;
#define ROW 2
#define COL 3

// �ӵ㣺k > list.size()ʱ����ת 

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// ��List�ĳ��� 
int getSize(ListNode* head) {
    int size = 0;
    while (head != NULL) {
        size++;
        head = head->next;
    }
    return size;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    // �����������Ҫ��ת��ֱ�����
    if (k <= 1 || head == NULL || getSize(head) < k)  return head;
    
    // ��ʱ�����������ڵ� 
    ListNode *newHead;               // ��ת�����ͷ��� 
    ListNode *preTemp = head;        // �����ڵ��ǰһ���ڵ� 
    ListNode *temp = head->next;     // ���ڱ����Ľڵ� 
    ListNode *nextTemp = temp->next; // �����ڵ�ĺ�һ���ڵ� 
    
    for (int i = 1; i < k; i++) {
        // �޸Ľڵ�ָ�� 
        temp->next = preTemp;
        // ���б�����ָ��ǰ�� 
        preTemp = temp;
        temp = nextTemp;
        if (temp != NULL)  nextTemp = temp->next;
    }
    
    // ��ͷ��㸳ֵ
    newHead = preTemp; 
    
    // δ��ת�ڵ�����
    head->next = reverseKGroup(temp, k);
    
    return newHead;
}

void addTestData(ListNode*& test, int& k) {
    k = 2;
    int data[ROW] = {1, 5};
    test = new ListNode(data[0]);
    ListNode *temp = test;
    for (int i = 1; i < ROW; i++) {
        temp->next = new ListNode(data[i]);
        temp = temp->next;
    }
}

void showOutput(ListNode *head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}


int main() {
    ListNode* test;
    int k;
    addTestData(test, k);
    showOutput(reverseKGroup(test, k));
}
