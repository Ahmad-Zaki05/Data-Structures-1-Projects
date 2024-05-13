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

node *dictionary = NULL;

//BASIC FUNCTIONS
node *constNode (char* data);
void deconNode (node *root);
node *insertNode (node *root, char* word);
node *searchNode (node *root, char* word);
void printInOrder (node *root);

//MAIN FUNCTIONS
void loadDictionary ();
void checkSentence (char* str);


int main () 
{
    loadDictionary();

    printf("Enter a sentence: ");
    char sentence[100];
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strlen(sentence)-1] = '\0'; //remove '\n'

    checkSentence(sentence);
    
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
    if (root == NULL|| strcasecmp(root->data, word) == 0) return root;
    if (strcasecmp(root->data, word) > 0) return searchNode(root->left, word);
    if (strcasecmp(root->data, word) < 0) return searchNode(root->right, word);
}

void printInOrder (node *root) {
    if (root == NULL) return ;
    printInOrder(root->left);
    printf("%s ", root->data);
    printInOrder(root->right);
}

void loadDictionary () {
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
    fclose(f);
}

void checkSentence (char* str) {
    char* token = strtok(str, " ");
    while (token != NULL)
    {
        if(searchNode(dictionary, token) != NULL)
            printf("%s - CORRECT\n", token);
        else
        {
            printf(("%s - INCORRECT, Suggestions: ")); 
            //call suggestions function
            printf("\n");
        }
        token = strtok(NULL, " ");
    }
}    