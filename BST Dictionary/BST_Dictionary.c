#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//STRUCT
typedef struct node {
    char* data;
    struct node *left, *right;
}node;

//BASIC FUNCTIONS
node *constNode (char* data);
void deconNode (node *root);
node *insertNode (node *root, char* word);
node *searchNode (node *root, char* word);
void printInOrder (node *root);

//MAIN FUNCTIONS
node *loadDictionary (node *dictionary);
int getHeight(node* node);
void checkSentence (node *dictionary, char* str);
char *getLast (node *dictionary, char *word);
char *getInorderPre (node *dictionary, char *word);
char *getInorderSucc (node *dictionary, char *word);

int main ()
{
    node *dictionary = NULL;

    dictionary = loadDictionary(dictionary);

    printf("Enter a sentence: ");
    char sentence[100];
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strlen(sentence) - 1] = '\0'; //remove '\n'

    checkSentence(dictionary, sentence);

    //printInOrder(dictionary);
    deconNode(dictionary);

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
    else if (strcasecmp(root->data, word) > 0) root->left = insertNode(root->left, word);
    else if (strcasecmp(root->data, word) < 0) root->right = insertNode(root->right, word);
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

node *loadDictionary (node *dictionary) {
    FILE *f = fopen("Dictionary.txt", "r");
    if (!f)
    {
        printf("FAILED TO OPEN FILE\n");
        exit(0);
    }

    char record[100];
    int count = 0;
    rewind(f);
    while(fgets(record, sizeof(record), f))
    {
        record[strlen(record)-1] = '\0'; //remove '\n'
        dictionary = insertNode(dictionary, record);
        count++;
    }

    printf("\n.................................\nDictionary Loaded Succesfully...!\n.................................\n");
    printf("Size: %d\n.................................\n", count);
    printf("Height: %d\n.................................\n", getHeight(dictionary));
    fclose(f);
    return dictionary;
}

void checkSentence (node *dictionary, char* str) {
    char* token = strtok(str, " ");
    while (token != NULL)
    {
        if(searchNode(dictionary, token) != NULL)
            printf("%s - CORRECT\n", token);
        else
        {
            printf(("%s - INCORRECT, Suggestions: "));
            //call suggestions function
            char *nearest = getLast(dictionary, token);
            printf("%s ", nearest);
            printf("\n");
        }
        token = strtok(NULL, " ");
    }
}

char *getLast (node *dictionary, char *word) {
    if (dictionary == NULL) return NULL;
    if (strcasecmp(dictionary->data, word) > 0 && dictionary->left != NULL) return getLast(dictionary->left, word);
    if (strcasecmp(dictionary->data, word) < 0 && dictionary->right != NULL) return getLast(dictionary->right, word);
    return dictionary->data;
}

int getHeight(node* node)
{
    if(node == NULL)
        return 0;
    else
    {
        int l = 1+getHeight(node->left);
        int r = 1+getHeight(node->right);
        return l>r ? l:r;
    }
}