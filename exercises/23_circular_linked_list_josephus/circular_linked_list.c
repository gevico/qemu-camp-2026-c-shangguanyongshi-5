#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    if (n <= 0) return NULL;
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 1; i <= n; ++i) {
        Node* node = (Node*)malloc(sizeof(Node));
        if (!node) {
            free_list(head);
            return NULL;
        }
        node->id = i;
        node->next = NULL;
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    tail->next = head;
    return head;
}

void free_list(Node* head) {
    if (!head) return;
    Node* cur = head->next;
    while (cur != head) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
    free(head);
}
