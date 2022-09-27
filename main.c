#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
    char data[1];
    struct node *next;
    int index;
}Node;

Node * push(Node *stackHead, char* value);
Node * pop(Node *stackHead);       
char * peek(Node *stackHead);    
bool isEmpty(Node *stackHead);
void freeStack(Node *stackHead);
bool isPalindrome(Node *stackHead);
Node * reverseStack(Node *stackHead);
Node * copyStack(Node *stackHead);

void menu();

Node *head;

int main(int argc, char const *argv[])
{
    menu();
    return 0;
}

Node * push(Node *stackHead, char* value){
    Node *element = malloc(sizeof(Node));
    element->index = 0;
    element->next = NULL;
    memcpy(element->data,value,sizeof(*value));
    
    if (isEmpty(stackHead))
    {   
        element->next = NULL;
        element->index = 0;
        stackHead = element;
    }
    else{
        element->index = stackHead->index;
        element->next = stackHead;        
        stackHead = element;
    }
    stackHead->index++;
    return stackHead;
}
Node * pop(Node *stackHead){
    if(!isEmpty(stackHead)){
        Node *element;
        element = stackHead;
        stackHead = stackHead->next;
        free(element);
        return stackHead;
    }
    return NULL;
}    
char * peek(Node *stackHead){
    return stackHead->data;
}    
bool isEmpty(Node *stackHead){
    if(head == NULL)
        return true;
    return false;
}
void freeStack(Node *stackHead){
    int size = 0;
    size = stackHead->index;
    for (int i = 0; i < size; i++)
        stackHead = pop(stackHead);
}
bool isPalindrome(Node *stackHead){
    Node * stackHeadBK = copyStack(stackHead);
    Node * reverse = reverseStack(stackHeadBK);
    Node * rCurrent = reverse;
    Node * sCurrent = stackHead;
    int size = stackHead->index;
    for(int i = 0; i < size; i++){
        if(strncmp(rCurrent->data, sCurrent->data, 1)){
            reverse = reverseStack(reverse);
            freeStack(reverse);
            return false;
        }
        rCurrent = rCurrent->next;
        sCurrent = sCurrent->next;
    }
    reverse = reverseStack(reverse);
    freeStack(reverse);
    return true;
}
Node * reverseStack(Node *stackHead){
    Node *prev, *current, *next;
    prev = NULL;
    current = NULL;
    next = NULL;
    current = stackHead; 
    prev = stackHead;
    current = current->next;
    prev->next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    stackHead = prev;
    return stackHead;
}
Node * copyStack(Node *stackHead){
    Node *current = stackHead;
    Node *newStack = malloc(sizeof(Node));
    newStack->next = NULL;
    while (current != NULL)
    {
        newStack = push(newStack, current->data);
        newStack->index = current->index;
        current = current->next;
    }
    newStack = reverseStack(newStack);
    Node *finalElement = newStack;
    newStack = newStack->next;
    free(finalElement);
    return newStack;
}
void menu(){
    char *value = malloc(sizeof(char));
    char *exitOption = malloc(sizeof(char));
    memcpy(exitOption, "x", sizeof(char));
    printf("Veja se uma palavra e um palindromo!\n");
    printf("-------------------------------------\n");
    while(true)
    {
        printf("Digite a letra a ser adicionada (Digite x para parar): \n");
        scanf(" %c", value);
        printf("-------------------------------------\n");
        if(*exitOption == *value){
            if(isPalindrome(head)){
                printf("Palindromo confirmado!\n");
            }else{
                printf("Infelizmente nao e um palindromo!\n");
            }
            free(value);
            free(exitOption);
            freeStack(head);
            break;
        }
        head = push(head, value);
    }
}