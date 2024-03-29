/*********************************************************************************
 ** CIS 26B: Advanced C
 ******************
 ** Homework 2A:
 **        Basic Stack and Queue Operations
 **********************************************************************************
  Pointers, Stacks & Queues

 There are a number of errors (about 10) in the following program.
 Locate all errors, fix them (as shown below), run the program and save its output
 as a comment at the end of the source file.
 Here is an example:
    int num = 10;
    int *ptr;
    num = &ptr; // <== Error: Comment the line and write the correct line below

    // num = &ptr; // Error #1
    ptr = &num;
 **********************************************************
 **  Written By: Aryan Garg
 **  IDE: VSCode / Gcc
 ***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define NUM_CLS 9

typedef struct
{
    char  course[10];
    int   noSections;
    int   sections[16];
} CIS_CLASS;


typedef struct node NODE;
struct node
{
    CIS_CLASS   data;
    // struct node next; error #1
	struct node *next;
};

void printClass(const CIS_CLASS *pStu);
NODE *push(NODE *stack, const CIS_CLASS *pStu);
NODE *pop(NODE **stack);
void enqueue(NODE **queue, NODE **rear, const CIS_CLASS *pStu);
NODE *dequeue(NODE **queue, NODE **rear);

int main (void)
{
    CIS_CLASS  clsList[NUM_CLS] =
    {
        {"CIS 35A", 2, {61, 63}},
        {"CIS 35B", 1, {62}},
        {"CIS 41A", 3, {1, 2, 61}},
        {"CIS 28",  1, {61}},
        {"CIS 22C", 4, {3, 4, 61, 63}},
        {"CIS 26B", 1, {61}},
        {"CIS 22B", 8, {1, 2, 3, 4, 6, 61, 62, 63}},
        {"CIS 29",  1, {61}},
        {"CIS 22A", 8, {1, 3, 5, 6, 7, 8, 61, 63}},
    };

    NODE *stack;
    NODE *top = NULL;
    NODE *queue = NULL, *rear = NULL;
    // NODE front; error #2
	NODE *front = NULL;
    int i, n, count = 4;

    // build stack and queue with data from an array of CIS_CLASS structures
    srand((unsigned int)time(NULL));
    for ( n = 0; n < count; n++)
    {
        i = rand() % NUM_CLS;
        //push(stack, &clsList[i]); error #3
		stack = push(stack, clsList+i);
        // enqueue(&queue, &rear, clsList[i]); error #4
		enqueue(&queue, &rear, clsList+i);
    }

    // display stack
    printf("STACK contents from top to bottom:\n");
    // while ((top = pop(stack))) // top != NULL error #5
	while((top = pop(&stack)))
    {
        printClass(&top->data);
		free(top); // error #6
    }
    printf("\n\n");

    // display queue
    printf("QUEUE contents from front to rear:\n");
    // while ((front = dequeue(queue, rear))) // front != NULL error #7
	while((front = dequeue(&queue, &rear)))
    {
        printClass(&front->data);
		free(front); // error #8
    }
    printf("\n\n");

#ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif

    return 0;
}
/***************************************************
 Displays the fileds of a CIS_CLASS structure
 Pre   pCls - a pointer to a CIS_CLASS structure
 Post
 */
void printClass(const CIS_CLASS *pCls)
{
    printf("%-10s %2d\n", pCls->course, pCls->noSections);
}
/***************************************************
 Stack Insert: insert in the beginning
 */
NODE *push(NODE *stack, const CIS_CLASS *pCls)
{
    NODE *pnew;

    pnew = (NODE *) malloc(sizeof (NODE));
    if (!pnew)
    {
        printf("... error in push!\n");
        exit(1);
    }
    pnew->data = *pCls;
    pnew->next = stack;
    stack = pnew;

    return stack;
}

/***************************************************
 Stack Delete: delete the first node
 */
NODE *pop(NODE **stack)
{
    NODE *first;

    if (*stack == NULL) return NULL;
    first = *stack;
    *stack = (*stack)->next;
    first->next = NULL;

    return first;
}

/***************************************************
 Queue Insert: insert at the end
 */
void enqueue(NODE **queue, NODE **rear, const CIS_CLASS *pCls)
{
    NODE *pnew;

    pnew = (NODE *) malloc(sizeof (NODE));
    if (!pnew)
    {
        printf("... error in enqueue!\n");
        exit(1);
    }
    pnew->data = *pCls;
    pnew->next = NULL;
    if (*queue == NULL) *queue = pnew;
    else (*rear)->next = pnew;
    *rear = pnew;
    return;
}

/***************************************************
 Queue Delete: remove the first node
 */
NODE *dequeue(NODE **queue, NODE **rear)
{
    NODE *first;

    if (*queue == NULL) return NULL;
    first = *queue;
    *queue = (*queue)->next;
    if (*queue == NULL) *rear = NULL;
    first->next = NULL;

    return first;
}

/*    ================= Sample Output ================= */
/*    Results:
STACK contents from top to bottom:
CIS 41A     3
CIS 29      1
CIS 22C     4
CIS 29      1


QUEUE contents from front to rear:
CIS 29      1
CIS 22C     4
CIS 29      1
CIS 41A     3
 */
