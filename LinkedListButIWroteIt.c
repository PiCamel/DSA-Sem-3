#include <stdio.h>
#include <stdlib.h>

/*
1. Inserting a node at the beginning of the list
2. Deleting a node from the beginning of the list
3. Print the list

4. Inserting a node at the end of the list
5. Deleting a node from the end of the list
*/

struct Node{
    int data;
    struct Node *next;
};
// Before the LL exists, initialise head node to perform functions on
struct Node *headNode = NULL;

void insertAtBeginning(int a);
void deleteFromBeginning(int *removedVal);
void insertAtEnd(int b);
void deleteFromEnd(int *removedVal);
void printList();

int main(){
    int removed = 0;
    printf("Testing linked-list operations:\n");
    insertAtBeginning(10);
    insertAtEnd(20);
    insertAtEnd(30);
    insertAtBeginning(5);
    printList();

    deleteFromBeginning(&removed);
    printf("Removed from beginning: %d\n", removed);

    deleteFromEnd(&removed);
    printf("Removed from end: %d\n", removed);

    printList();

    return 0;
}

void insertAtBeginning(int a){
    struct Node* newHead = (struct Node*)malloc(sizeof(struct Node));
    if (!newHead){
        printf("Malloc failed, can't add node at beginning.\n");
        return;
    }
    newHead->next = headNode;
    newHead->data = a;
    //Now the previous head isn't the head anymore so
    headNode = newHead;
    printf("Success! %d added to the beginning.\n", a);
    return;
}

void insertAtEnd(int b){
    struct Node* newTail = (struct Node*)malloc(sizeof(struct Node));
    if (!newTail){
        printf("Malloc failed, can't add node at end.\n");
        return;
    }
    struct Node* tail = headNode;
    while (tail && tail->next) tail = tail->next; // Finds existing last node
    newTail->next = NULL;
    newTail->data = b;
    tail->next = newTail;
    printf("Success! %d added to the end.\n", b);
    return;
}

void deleteFromBeginning(int* removedVal){
    struct Node* temp = headNode; //Needed to free head AFTER changing head to head->next
    if (!temp){
        printf("Head node not found.\n");
        return;
    }
    *removedVal = temp->data;
    headNode = headNode->next;
    free(temp);
    printf("Success, %d node deleted from beginning\n", *removedVal);
    return;
}

void deleteFromEnd(int* removedVal){
    struct Node* temp = headNode;
    if (!temp){
        printf("Head node not found.\n");
        return;
    }
    while (temp->next->next) temp = temp->next; //Locates second to last node. (>= 2 nodes)
    if (!headNode->next){
        *removedVal = headNode->data;
        free(headNode);
        headNode = NULL;
        printf("Success, %d node deleted from end.\n", *removedVal);
        return;
    }
    *removedVal = temp->next->data;
    free(temp->next);
    temp->next = NULL;
    printf("Success, %d node deleted from end.\n", *removedVal);
    return;
}

void printList(){
    struct Node* curNode = headNode;
    if (!headNode){
        printf("List does not contain any elements.\n");
        return;
    }
    printf("List is: ");
    while (curNode){
        printf("%d",curNode->data);
        if (curNode->next) printf("->");
        curNode = curNode->next;
    }
    printf("\n");
    return;
}