#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int add;                    // ��һλ�ļ�ֵ��0/1 
    ListNode* returnListHead;   // ���ص�����ͷ 
    ListNode* returnTemp;       // ���ڱ������ص����� 
    ListNode* temp;             // �����ýڵ㣬�������������нϳ����� 
    
    // ��Ϊ��һ��ֵȷ��������ֱ�ӽ��г�ʼ�� 
    returnListHead = new ListNode((l1->val + l2->val) % 10);
    returnTemp = returnListHead;
    add = (l1->val + l2->val) / 10;
    
    // ����ѭ����� 
    while (1) {
        l1 = l1->next;
        l2 = l2->next;
        
        if (l1 == NULL) {
            temp = l2;
            break;
        }
        if (l2 == NULL) {
            temp = l1;
            break;
        }
        
        // ������ӣ�add�޸�ֵ 
        returnTemp->next = new ListNode((l1->val + l2->val + add) % 10);
        add = (l1->val + l2->val + add) / 10;
        returnTemp = returnTemp->next;
    }
        
    while (temp != NULL) {
        // ������ӣ�add�޸�ֵ 
        returnTemp->next = new ListNode((temp->val + add) % 10);
        add = (temp->val + add) / 10;
        returnTemp = returnTemp->next;
        temp = temp->next;
    }
    
    // �������һ����λ��������Ͻ�λ 
    if (add == 1)
        returnTemp->next = new ListNode(1);
    
    return returnListHead;
}

void addTestData(ListNode*& test1, ListNode*& test2) {
    int data1[100] = {2, 4, 3};
    int n1 = 3;
    int data2[100] = {5, 6, 4};
    int n2 = 3;
    
    ListNode* temp; 
    test1 = new ListNode(data1[0]);
    temp = test1;
    for (int i = 1; i < n1; i++) {
        temp->next = new ListNode(data1[i]);
        temp = temp->next;
    }
    
    test2 = new ListNode(data2[0]);
    temp = test2;
    for (int i = 1; i < n2; i++) {
        temp->next = new ListNode(data2[i]);
        temp = temp->next;
    }
}

void showOutput(ListNode* output) {
    cout << output->val;
    output = output->next;
    while (output != NULL) {
        cout << "->" << output->val;
        output = output->next;
    }
    cout << endl;
}

int main() {
    ListNode* test1;
    ListNode* test2;
    addTestData(test1, test2);
    showOutput(addTwoNumbers(test1, test2)); 
}
