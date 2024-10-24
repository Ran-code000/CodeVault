#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define InitSize 10
typedef struct{
    int* data;
    int MaxSize;
    int length;
}SeqList;
void InitList(SeqList& l){
    l.data = (int*) malloc(InitSize * sizeof(int));
    l.length = 0;
    l.MaxSize = InitSize;
}
void DestroyList(SeqList& l){
    free(l.data);
    l.length = 0;
    l.MaxSize = 0;
}
void ListInsert(SeqList& l, int pos, int val){
    if(pos > l.length){
        printf("Out of range!!!\n");
        return;
    } 
    int* temp = (int*) malloc((l.length + 1) * sizeof(int));
    memcpy(temp, l.data, sizeof(int) * pos);
    temp[pos] = val;
    memcpy(temp + pos + 1, l.data + pos, sizeof(int) * (l.length - pos));
    free(l.data);
    l.data = temp;
    l.MaxSize++;
    l.length++;
}
bool LocateElem(SeqList& l, int val){
    for(int i = 0; i < l.length; i++) if(l.data[i] == val) return true;
    return false;
}
int GetElem(SeqList& l, int id){ return l.data[id];}
int Length(SeqList& l){ return l.length;}
void PrintList(SeqList& l){ for(int i = 0; i < l.length; i++) printf("%d", l.data[i]);}
bool Empty(SeqList& l){ return l.length == 0;}
void IncreaseSise(SeqList& l, int addlen){
    int* temp = (int*) malloc((l.length + addlen) * sizeof(int));
    memcpy(temp, l.data, sizeof(int) * l.length);
    l.MaxSize = l.length + addlen;
}
int main(){
    SeqList l;
    InitList(l);
    ListInsert(l, 0, 0);
    ListInsert(l, 1, 1);
    ListInsert(l, 2, 2);
    ListInsert(l, 3, 3);
    ListInsert(l, 4, 4);
    ListInsert(l, 5, 5);
    ListInsert(l, 1, 1);
    ListInsert(l, 3, 3);
    ListInsert(l, 5, 5);
    ListInsert(l, 7, 7);
    ListInsert(l, 9, 9);
    ListInsert(l, 11, 11);
    printf("The list is :");
    PrintList(l);
    printf("\n");
    printf("The length of the seqlist is %d\n", l.length);
    ListInsert(l, 12, 100);
    //ListInsert(l, 14, 999);
    printf("The list is :");
    PrintList(l);
    printf("\nThe forth number is %d\n", GetElem(l, 4));
    printf("Is empty or not : %d\n", Empty(l));
    IncreaseSise(l, 7);
    printf("After increase the size of seqlist(addlen = 7), length = %d, maxsize = %d", l.length, l.MaxSize);
    return 0;
}