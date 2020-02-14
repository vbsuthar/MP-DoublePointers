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
#include <stdbool.h>

typedef struct student student;
struct student {
    char *name;
    char *major;
    int id;
};

struct grade_node {
    int value;
    char assignment[255];
    struct grade_node *next;
};

void insert_grades(struct grade_node *head);

void create_head1(struct grade_node *head);
struct grade_node *create_head2(struct grade_node *head);
void create_head3(struct grade_node **head);

struct grade_node *insert_grade_head(struct grade_node **head);
struct grade_node *insert_grade_tail(struct grade_node **head);

#define nameSize 50

#define majorSize 20

void destroy_student(student **s)
{
    free ((*s)->name);
    free ((*s)->major);
    free (*s);
    *s = NULL;
}

/*
 * 
 */
int main(int argc, char** argv) {

    // start by defining an allocating a linked list for grade_node;
    // it is NULL as it does not have any members in the list yet
    struct grade_node *head = NULL;
    bool done = false;
    do {
        int option;
        printf("\n\n What would you like to do? \n");
        printf(" 1 - add a grade_node to the tail\n");
        printf(" 2 - add a grade_node to the head\n");
        printf(" 0 - to quit \n");
        scanf("%d", &option);
        if (option <= 0)
        {
            done = true;
        }
        else
            if (option == 1) insert_grade_tail(&head);
            else if (option == 2) insert_grade_head(&head);
            printf("\n\n In main - head = %p", head);
    } while (done == false);

    

    return (EXIT_SUCCESS);
}

struct grade_node *insert_grade_head(struct grade_node **head)
{
    // check if there are any and if not create the head
    if (*head == NULL) create_head1(*head);
    // creating head of the list 
    printf("\n head address in insert_grade_head() with create_head1() : %p", *head);
    // note this address will still be null as the call to create_head1() will create
    // a pointer to a grade_node struct on the stack.   The create_head1() does create the space
    // but the value is lost as the address is put on the stack and never copied.
    // there are two options to fix this - either pass in the pointer to the pointer of 
    // the head or return the address and assign it as in the below.
    // you could also do both of the above or you could make head a global variable (not desirable)
    if (*head == NULL) 
        *head = create_head2(*head);
    printf("\n head address in insert_grade_head() with create_head2() : %p", *head);
    // note that worked but here is another way
    free(*head);
    *head = NULL;
    if (*head == NULL)
        create_head3(head);
    printf("\n head address in insert_grade_head() with create_head3() : %p", *head);
 
    return *head;
}

struct grade_node *insert_grade_tail(struct grade_node **head)
{
  return *head;  
}

void create_head1(struct grade_node *head)
{
    head = malloc(sizeof(struct grade_node *));
    printf("\n head created - address : %p", head);
}

struct grade_node *create_head2(struct grade_node *head)
{
    head = malloc(sizeof(struct grade_node *));
    printf("\n head created - address : %p", head);
    return head;
}

void create_head3(struct grade_node **head)
{
    // now we have a pointer to the address of the head
    *head = malloc(sizeof(struct grade_node *));
    printf("\n head created - address : %p", *head);
}