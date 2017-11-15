#include <iostream>
#include <stack>
using namespace std;
#define ROW 2
#define COL 3

// 坑点：k > list.size()时不反转 

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 求List的长度 
int getSize(ListNode* head) {
    int size = 0;
    while (head != NULL) {
        size++;
        head = head->next;
    }
    return size;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    // 三种情况不需要反转，直接输出
    if (k <= 1 || head == NULL || getSize(head) < k)  return head;
    
    // 此时至少有两个节点 
    ListNode *newHead;               // 反转后的新头结点 
    ListNode *preTemp = head;        // 遍历节点的前一个节点 
    ListNode *temp = head->next;     // 用于遍历的节点 
    ListNode *nextTemp = temp->next; // 遍历节点的后一个节点 
    
    for (int i = 1; i < k; i++) {
        // 修改节点指向 
        temp->next = preTemp;
        // 所有遍历用指针前移 
        preTemp = temp;
        temp = nextTemp;
        if (temp != NULL)  nextTemp = temp->next;
    }
    
    // 对头结点赋值
    newHead = preTemp; 
    
    // 未反转节点链接
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
