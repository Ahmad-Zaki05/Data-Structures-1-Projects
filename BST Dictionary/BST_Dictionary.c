#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct node {
    char* data;
    struct node *left, *right;
}node;

node *constNode (char* data);
void deconNode (node *root);
node *insertNode (node *root, char* word);
node *searchNode (node *root, char* word);
void printInOrder (node *root);

int main () {

    node *root = NULL;
    root = insertNode(root, "b");
    root = insertNode(root, "a");
    root = insertNode(root, "ab");
    root = insertNode(root, "c");
    printInOrder(root);
    deconNode(root);

    return 0;
}

node *constNode (char* data) {
    node *n = malloc(sizeof(node));
    n->data = malloc(strlen(data) + 1);
    strcpy(n->data, data);
    n->left = NULL;
    n->right = NULL;
    return n;
}

void deconNode (node *root) {
    if (root == NULL) return;
    deconNode(root->left);
    deconNode(root->right);
    free(root->data);
    free(root);
}

node *insertNode (node *root, char* word) {
    if (root == NULL) root = constNode(word);
    if (strcasecmp(root->data, word) > 0) root->left = insertNode(root->left, word);
    if (strcasecmp(root->data, word) < 0) root->right = insertNode(root->right, word);
    return root;
}

node *searchNode (node *root, char* word) {
    if (root == NULL || strcasecmp(root->data, word) == 0) return root;
    if (strcasecmp(root->data, word) > 0) return searchNode(root->left, word);
    if (strcasecmp(root->data, word) < 0) return searchNode(root->right, word);
}

void printInOrder (node *root) {
    if (root == NULL) return ;
    printInOrder(root->left);
    printf("%s ", root->data);
    printInOrder(root->right);
}
