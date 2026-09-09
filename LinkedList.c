#include <stdio.h>
#include <stdlib.h>

// Singly linked list implementation

struct Node {
    int data;
    struct Node* next;
};

static struct Node* head = NULL;

// Insert node at the beginning
void insertAtBeginning(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        perror("malloc");
        return;
    }
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// Delete a node from the beginning. Returns the deleted value via *out and
// returns 1 on success, 0 if the list was empty.
int deleteFromBeginning(int *out) {
    if (!head) return 0;
    struct Node* tmp = head;
    *out = tmp->data;
    head = head->next;
    free(tmp);
    return 1;
}

// Print the list
void printList(void) {
    struct Node* cur = head;
    if (!cur) {
        printf("List is empty.\n");
        return;
    }
    printf("List: ");
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

// Insert a node at the end
void insertAtEnd(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        perror("malloc");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (!head) {
        head = newNode;
        return;
    }

    struct Node* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = newNode;
}

// Delete a node from the end. Returns the deleted value via *out and
// returns 1 on success, 0 if the list was empty.
int deleteFromEnd(int *out) {
    if (!head) return 0;
    if (!head->next) {
        *out = head->data;
        free(head);
        head = NULL;
        return 1;
    }
    struct Node* cur = head;
    struct Node* prev = NULL;
    while (cur->next) {
        prev = cur;
        cur = cur->next;
    }
    // cur is last node, prev is penultimate
    *out = cur->data;
    prev->next = NULL;
    free(cur);
    return 1;
}

int main(void) {
    int choice, val, ok;

    while (1) {
        printf("\nChoose operation:\n");
        printf("1. Insert at beginning\n");
        printf("2. Delete from beginning\n");
        printf("3. Insert at end\n");
        printf("4. Delete from end\n");
        printf("5. Print list\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Value to insert at beginning: ");
                if (scanf("%d", &val) != 1) return 0;
                insertAtBeginning(val);
                break;
            case 2:
                ok = deleteFromBeginning(&val);
                if (ok) printf("Deleted from beginning: %d\n", val);
                else printf("List is empty.\n");
                break;
            case 3:
                printf("Value to insert at end: ");
                if (scanf("%d", &val) != 1) return 0;
                insertAtEnd(val);
                break;
            case 4:
                ok = deleteFromEnd(&val);
                if (ok) printf("Deleted from end: %d\n", val);
                else printf("List is empty.\n");
                break;
            case 5:
                printList();
                break;
            case 6:
                // free remaining nodes
                while (deleteFromBeginning(&val)) ;
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}