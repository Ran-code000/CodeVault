/*************************************************************************
	> File Name: 27.linklist.c
	> Author:Xin 
	> Mail:2923262959@qq.com 
	> Created Time: Fri 29 Dec 2023 08:29:59 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
int len;

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *Getvalue(int Val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = Val;
    p->next = NULL;
    return p;
}

Node *insert(Node *head, int pos, int Val) {
    Node new_head, *p = &new_head, *node = Getvalue(Val);
    new_head.next = head;
    for (int i = 0; i < pos; i++) p = p->next;
    node->next = p->next;
    p->next = node;
    return new_head.next;
}

void clear(Node *head) {
    if (head == NULL) return ;
    for (Node *p = head, *q; p; p = q) {
        q = p->next;
        free(p);
    }
    return ;
}

void PrintList(Node *head) {
    int n = 0;
    for (Node *p = head; p; p = p->next) n++;
    for (int i = 0; i < n; i++) {
        len = printf("%3d   ", i);
    }
    printf("\n");
    for (Node *p = head; p; p = p->next) {
        printf("%3d ->", p->data);
    }
    printf("\n\n");
    return ;
}

void find(Node *head, int val) {
    Node *p = head;
    int c = 0;
    char d = ' ';
    while (p) {
        if (p->data == val) {
            for(int i = 0; i < c * len + 2; i++) {
                printf(" ");
            }
            printf("^\n");
            for(int i = 0; i < c * len + 2; i++) {
                printf(" ");
            }
            printf("|\n");
            return ;
        }
        p = p->next;
        c++;
    }
    printf("There is no %d in this linklist\n", val);
    return ;
}


int main() {
    srand(time(0));
    Node *head = NULL;
    for (int i = 0; i < MAX; i++) {
        int pos = rand() % (i + 1), val = rand() % 100;
        printf("insert %d at %d to the linklist\n", val, pos);
        head = insert(head, pos, val);
        PrintList(head);
    }
    int n;
    while (scanf("%d", &n) != EOF) {
        find(head, n);
    }
    clear(head);
    return 0;
}
