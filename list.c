#include "list.h"
#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>
#include <ctype.h>
//static struct List temp2[100];
// struct List* List_create(){
//     struct Node *ptr1 = (struct Node*)malloc(sizeof(struct Node)); 
//     ptr1->name = NULL; 
//     ptr1->next = NULL; 
//     struct List* temp2= (struct List*)malloc(sizeof(struct List));
//     temp2->headList = ptr1;

//     return temp2;
// }
void insert(struct Node** nodeList, char* name) 
{ 
    struct Node *ptr1 = (struct Node*)malloc(sizeof(struct Node)); 
    ptr1->name = name; 
    ptr1->next = *nodeList; 
    *nodeList = ptr1; 
} 

  

void bubbleSort(struct Node* nodeList) 
{ 
    int swapped = 1;
    struct Node *ptr1; 
    struct Node *lptr = NULL; 
  
   
    if (nodeList == NULL) 
        return;
  
    while (swapped){
        swapped = 0; 
        ptr1 = nodeList; 
  
        while (ptr1->next != lptr) 
        { 
            if (strcmp( ptr1->name,ptr1->next->name)>0) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    }
} 
  

void swap(struct Node *a, struct Node *b) 
{ 
    char* temp = malloc(sizeof(char*)); 
    strcpy(temp,a->name);
    strcpy(a->name,b->name);
    strcpy(b->name,temp);
    free(temp);
} 
void print(struct Node* nodeList) 
{ 
    struct Node *temp = nodeList; 
    while (temp!=NULL) 
    { 
        printf("%s\n", temp->name); 
        temp = temp->next; 
    } 
} 