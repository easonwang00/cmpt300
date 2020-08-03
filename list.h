#ifndef _LIST_H_
#define _LIST_H_
#include<stdio.h> 
#include<stdlib.h> 
struct Node{
	char* name;
	struct Node* next;
};
// struct List{
// 	struct Node* headList;
// };
// struct List* List_create();
void insert(struct Node** nodeList, char* name);
void bubbleSort(struct Node* nodeList);
void swap(struct Node *a, struct Node *b);
void print(struct Node* nodeList);
#endif