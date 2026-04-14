#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    QueueNode *qn = (QueueNode *)malloc(sizeof(QueueNode));
    if (!qn) return;
    qn->tree_node = tree_node;
    qn->next = NULL;
    if (q->rear) q->rear->next = qn;
    else q->front = qn;
    q->rear = qn;
}

TreeNode* dequeue(Queue *q) {
    if (is_empty(q)) return NULL;
    QueueNode *front = q->front;
    TreeNode *node = front->tree_node;
    q->front = front->next;
    if (!q->front) q->rear = NULL;
    free(front);
    return node;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    if (!level_order || size <= 0 || level_order[0] == INT_MIN) return NULL;
    TreeNode *root = (TreeNode *)calloc(1, sizeof(TreeNode));
    if (!root) return NULL;
    root->val = level_order[0];

    Queue *q = create_queue();
    if (!q) {
        free(root);
        return NULL;
    }
    enqueue(q, root);

    int idx = 1;
    while (idx < size && !is_empty(q)) {
        TreeNode *parent = dequeue(q);
        if (idx < size && level_order[idx] != INT_MIN) {
            TreeNode *left = (TreeNode *)calloc(1, sizeof(TreeNode));
            if (left) {
                left->val = level_order[idx];
                parent->left = left;
                enqueue(q, left);
            }
        }
        idx++;
        if (idx < size && level_order[idx] != INT_MIN) {
            TreeNode *right = (TreeNode *)calloc(1, sizeof(TreeNode));
            if (right) {
                right->val = level_order[idx];
                parent->right = right;
                enqueue(q, right);
            }
        }
        idx++;
    }
    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    if (!root) return;
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    if (!root) return;
    size_t cap = 16;
    size_t top = 0;
    TreeNode **stack = (TreeNode **)malloc(sizeof(TreeNode *) * cap);
    if (!stack) return;
    stack[top++] = root;
    while (top > 0) {
        TreeNode *node = stack[--top];
        printf("%d ", node->val);
        if (node->right) {
            if (top == cap) {
                cap *= 2;
                TreeNode **ns = (TreeNode **)realloc(stack, sizeof(TreeNode *) * cap);
                if (!ns) break;
                stack = ns;
            }
            stack[top++] = node->right;
        }
        if (node->left) {
            if (top == cap) {
                cap *= 2;
                TreeNode **ns = (TreeNode **)realloc(stack, sizeof(TreeNode *) * cap);
                if (!ns) break;
                stack = ns;
            }
            stack[top++] = node->left;
        }
    }
    free(stack);
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
