#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIST_LEN 20

typedef struct node {
    int val;
    struct node* next;
} node;

node* head = NULL;
node* currNode = NULL;
int currIndex = 0;

// ��������������ʵ���ڵ��value
void initList() {
    node* tnp;
    for (int i = 0; i < LIST_LEN; i++) {
        node* tn = (node*)malloc(sizeof(node));
        tn->next = NULL;
        tn->val = 2 + rand() % 7;
        if (!i) {
            head = tnp = tn;
            continue;
        }
        tnp->next = tn;
        tnp = tn;
    }
}

// �����ȣ���ʵ����LSIT_LEN
int listLen() {
    if (!head) return 0;
    int i = 1;
    node* tnp = head;
    while (tnp->next) {
        ++i;
        tnp = tnp->next;
    }
    return i;
}

// �����������нڵ㷴��
void reverse() {
    if (!head) return;
    int len = listLen();
    int arr[len];

    node* tnp = head;
    for (int i = 0; i < len; i++) {
        arr[i] = tnp->val;
        tnp = tnp->next;
    }

    tnp = head;
    for (int i = 0; i < len; i++) {
        tnp->val = arr[len - i - 1];
        tnp = tnp->next;
    }
}

// ��ӡ�б�
void printList() {
    if (!head) return;
    int len = listLen();
    node* tnp = head;
    for (int i = 0; i < len; i++) {
        printf("%d ", tnp->val);
        tnp = tnp->next;
    }
    printf("\n");
}

int searchFive() {
    if (!head) return -1;
    if (currIndex >= listLen()) return -1;
    if (!currIndex) currNode = head;
    node* tnp;
    for (int i = currIndex; i < listLen(); i++) {
        tnp = currNode;
        ++currIndex;
        currNode = currNode->next;
        if (tnp->val == 5) return currIndex - 1;
    }
    return -1;
}

int main() {
    srand(time(0));
    
    // ����һ�������������ʵ�ָ��ڵ�value
    initList();
    // ��ӡ�б�
    printf("the list is: ");
    printList();
    // ��˳������Ϊ5�Ľڵ㣬����������(��0��ʼ)
    int index;
    while ((index = searchFive()) != -1) {
        printf("next node with value 5: %d\n", index);
    }
    // �����������нڵ㷴��
    reverse();
    // ��ӡ�б�
    printf("after reverse: ");
    printList();

    system("pause");
    return 0;
}