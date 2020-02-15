/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: vijay
 *
 * Created on February 14, 2020, 12:56 PM
 */

#include <stdio.h>
#include <stdlib.h>


struct grade_node {
    int value;
    char assignment[255];
    struct grade_node *next;
};


void create_head1(struct grade_node *head);
struct grade_node *create_head2(struct grade_node *head);
void create_head3(struct grade_node **head);



/*
 * 
 */
int main(int argc, char** argv) {

    // start by defining an allocating a linked list for grade_node;
    // it is NULL as it does not have any members in the list yet
    struct grade_node *head = NULL;
    
    // lets create the first element
    head = malloc(sizeof(struct grade_node));
    // now the head points to the first element.
    printf("\n Head as created in main() add: %p", head);
    free(head);   // release memory 
    head = NULL;
    // but what happens if we want to make this modular code (highly recommended)
     if (head == NULL) create_head1(head);
   // creating head of the list 
    printf("\n head address in main with create_head1() : %p", head);
    printf("\n NOTE:  head address in main() did not change!!!\n");
    // note this address will still be null as the call to create_head1() will create
    // a pointer to a grade_node struct on the stack.   The create_head1() does create the space
    // but the value is lost as the address is put on the stack and never copied.
    // there are two options to fix this - either pass in the pointer to the pointer of 
    // the head or return the address and assign it as in the below.
    // you could also do both of the above or you could make head a global variable (not desirable)
    if (head == NULL) 
        head = create_head2(head);
    printf("\n head address in main created with create_head2() : %p", head);
    printf("\n NOTE:  head address in main() worked correctly as a return value!!!\n");
    // note that worked but here is another way
    free(head);
    head = NULL;
    if (head == NULL)
        create_head3(&head);
    printf("\n head address in main created with create_head3() : %p", head);
    printf("\n NOTE:  head address in main() worked correctly when passed as a double pointer!!!\n");
 
    return (EXIT_SUCCESS);
}


void create_head1(struct grade_node *head)
{
    head = malloc(sizeof(struct grade_node));
    printf("\n head created create_head()- address : %p", head);
}

struct grade_node *create_head2(struct grade_node *head)
{
    head = malloc(sizeof(struct grade_node));
    printf("\n head created in create_head2() - address : %p", head);
    return head;
}

void create_head3(struct grade_node **head)
{
    // now we have a pointer to the address of the head
    *head = malloc(sizeof(struct grade_node *));
    printf("\n head created create_head3()- address : %p", *head);
}