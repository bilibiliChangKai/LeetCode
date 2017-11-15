#include <iostream>
#include <vector>
using namespace std;
#define ROW 3
#define COL 3

// �ӵ㣺����Ϊ�� 

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void showOutput(ListNode *head); 
// ��������������ϳ�һ�� 
ListNode* TwoListstoOne(ListNode *h1, ListNode *h2) {
    ListNode *newHeadPre = new ListNode(0);  // ����ͷ����ǰһ���ڵ� 
    ListNode *newTemp = newHeadPre;          // ���ڱ����Ľڵ�
    
    // ��С��ֵ���������� 
    while (h1 != NULL || h2 != NULL) {
        if (h1 == NULL || (h2 != NULL && h1->val > h2->val)) {
            newTemp->next = new ListNode(h2->val);
            h2 = h2->next;
        }
        else {
            newTemp->next = new ListNode(h1->val);
            h1 = h1->next; 
        }
        newTemp = newTemp->next;
    } 
    
    return newHeadPre->next;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    // ����Ϊ�� 
    if (lists.empty())  return NULL;
     
    while (lists.size() > 1) {
        // ��ǰ��������ϲ��������� 
        lists.push_back(TwoListstoOne(lists[0], lists[1]));
        
        // ɾ��������
        lists.erase(lists.begin(), lists.begin() + 2); 
    } 
    
    return lists[0];
}

void addTestData(vector<ListNode*>& test) {
    int data[ROW][COL] = {
    1, 3, 5,
    2, 2, 2,
    3, 5, 10};
    for (int i = 0; i < ROW; i++) {
        ListNode *headPre = new ListNode(0);
        ListNode *temp = headPre;
        for (int j = 0; j < COL; j++) {
            //cout << "dataij:" << data[i][j] << endl;
            temp->next = new ListNode(data[i][j]);
            temp = temp->next;
        }
        test.push_back(headPre->next);
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
    vector<ListNode*> test;
    addTestData(test);
    showOutput(mergeKLists(test));
}
