#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node node;
struct node {
    float data;
     node *next;
};

typedef struct {
    node *head;
} Stack;

// PART 1: Stack Functions
Stack* initialize ();
float pop (Stack *s);
void push (Stack *s, float value);
float peek (Stack *s);
int isEmpty (Stack *s);

// PART 2: Infix to Postfix
char* infixTopostfix (char *infix);
int priority(char c);
int isNum(char *str);


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

int priority (char c) {
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

char* infixTopostfix (char *infix) {
    Stack *s = initialize();
    char *post = malloc(strlen(infix)+1);
    int j = 0;
    char *token = strtok(infix, " ");
    while(token != NULL) 
    {
       if (isNum(token))
       {
            strcpy(post + j*sizeof(char), token);
            j += strlen(token);
            post[j++] = ' ';
       }
        else if (isEmpty(s))
            push(s, (float)(token[0]));
        else if (token[0] == ')')
        {
            while (!isEmpty(s) && (char)(peek(s)) != '(')
            {
                post[j++] = (char)(pop(s));
                post[j++] = ' ';
            }
            pop(s);
        }
        else
        {
            while (!isEmpty(s) && priority((char)(peek(s))) >= priority(token[0]) && token[0] != '(')
            {
                post[j++] = (char)(pop(s));
                post[j++] = ' ';
            }
            push(s, (float)(token[0]));
        }
        token = strtok(NULL, " ");
    }
    while(!isEmpty(s)) 
    {
        post[j++] = (char)(pop(s));
        if(!isEmpty(s))
            post[j++] = ' ';
    }
    post[j] = '\0';
    deconStack(s);
    return post;
}

int isNum(char *str) {
    char *endptr;
    float num = strtof(str, &endptr);
    if (endptr == str)
        return 0;
    else 
        return 1;
}



int main()
{
    char infix[] = "2 + ( -2.5 + 3.14 ) * ( -5.4 + 8.1 ) ^ ( -0.5 )";

    char *post = infixTopostfix(infix);

    printf("%s", post);

    return 0;
}
