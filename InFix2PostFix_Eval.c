#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    float data;
    struct node *next;
} node;

typedef struct {
    node *head;
} Stack;

// PART 1 (stack functions)
Stack* initialize ();
float pop (Stack *s);
void push (Stack *s, float value);
float peek (Stack *s);
int isEmpty (Stack *s);


Stack* initialize () {
    Stack *s = malloc(sizeof(Stack));
    s->head = NULL;
    return s;
}

node* constNode (float data) {
    node *n = malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    return n;
}

void deconNode (node* n) {
    free(n);
}

void deconStack (Stack *s) {
    if (s->head == NULL) {
        free(s);
        return ;
    }
    node *temp = s->head;
    s->head = s->head->next;
    while (s->head != NULL) {
        deconNode(temp);
        temp = s->head;
        s->head = s->head->next;
    }
    free(temp);
    free(s);
}

void push (Stack *s, float value) {
    node *n = constNode(value);
    if (s->head == NULL) {
        s->head = n;
        return ;
    }
    n->next = s->head;
    s->head = n;
}

int isEmpty (Stack *s) {
    return (s->head == NULL);
}

float pop (Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is already empty\n");
        return -10000;
    }
    node *n = s->head;
    s->head = s->head->next;
    float value = n->data;
    free(n);
    return value;
}

float peek (Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -10000;
    }
    return s->head->data;
}

void display(Stack *s) {
    if (s->head == NULL) {
        printf("Stack is empty\n");
        return ;
    }
    node *temp = s->head;
    while (temp != NULL) {
        printf("%f ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{

    Stack *s = constStack();
    deconStack(s);

    return 0;
}
