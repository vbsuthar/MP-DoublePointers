/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Vijay Suthar
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
void twoDArraysDemo(void);


/*
 * 
 */
int main(int argc, char** argv) {

    // start by defining an allocating a linked list for grade_node;
    // it is NULL as it does not have any members in the list yet
    struct grade_node *head = NULL, *head2 = NULL, *head3 = NULL;
    struct grade_node *headCreateInFunction = NULL;
    
    // lets create the first element
    head = malloc(sizeof(struct grade_node));
    // now the head points to the first element.
    printf("\n Head as created in main() add: %p", head);
    
    // but what happens if we want to make this modular code (highly recommended)
    create_head1(headCreateInFunction);
   // creating head of the list 
    printf("\n head address in main with create_head1() : %p", headCreateInFunction);
    printf("\n NOTE:  head address in main() did not change!!!\n");
    // note this address will still be null as the call to create_head1() will create
    // a pointer to a grade_node struct on the stack.   The create_head1() does create the space
    // but the value is lost as the address is put on the stack and never copied.
    // there are two options to fix this - either pass in the pointer to the pointer of 
    // the head or return the address and assign it as in the below.
    // you could also do both of the above or you could make head a global variable (not desirable)
    if (head2 == NULL) 
        head2 = create_head2(head2);
    printf("\n head address in main created with create_head2() : %p", head2);
    printf("\n NOTE:  head address in main() worked correctly as a return value!!!\n");
    // note that worked but here is another way

    head3 = NULL;
    if (head3 == NULL)
        create_head3(&head3); // effectively being passed as a double pointer
    printf("\n head address in main created with create_head3() : %p", head3);
    printf("\n NOTE:  head address in main() worked correctly when passed as a double pointer!!!\n");
 
    // Now call function to demo doing 2D arrays
    twoDArraysDemo();

    free(head);   // release memory 
    free(headCreateInFunction);
    free(head2);
    free(head3);
    
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

void twoDArraysDemo(void)
{
#define numRows   4
#define maxCols   6
/*
 * lets say we want to have to implement a 2D array but the number of columns per row 
 * is variable.   You could use a 2D with the number of rows and then allocate the max
 * for the number of columns.
*/
   int array2Dstatic[numRows][maxCols];
/* 
 * this would be perfectly fine in most cases - however what happens if maxCols
 * is to large or you can't afford the memory or there are other reasons to keep the 
 * numCol for each row dynamic.   In this case you could you use an a double pointer
 * as below.
*/
    int **array2Ddynamic;
       
    // first get memory to point to the location of numRows rows.  
    // NOTE:  None of the columns are allocated yet.  
    array2Ddynamic = malloc(numRows * sizeof(int *));
    
    // this will print out what is inside of the location of the rows
    // initially could be junk - initially is compiler dependent - gcc inits to 0
    printf("\n The initial values for the pointers to each row");
    for(int i = 0; i < numRows; ++i) printf("\n %p", array2Ddynamic[i]);
    
    // now lets allocate memory for each column.   For this example lets assume we 
    // need twice as many column as the row index (1-based) i.e. row index 2 would need 6 columns
    for(int i = 0; i < numRows; ++i) array2Ddynamic[i] = malloc((i+1)*2*sizeof(int));
    // print out starting location of each row.   Note the spacing between addresses
    // spacing is not uniform like normal 2D tables / arrays would be.
    printf("\n The values for the pointers to each row after columns allocated");
    for(int i = 0; i < numRows; ++i) printf("\n %p", array2Ddynamic[i]);
    // lets init the value of the columns as the row number
    for(int i = 0; i < numRows; ++i)
        for(int j = 0; j < (i+1); ++j) array2Ddynamic[i][j] = i;
    // now print out each row.
    printf("\n the 2D table entries now");
    for(int i = 0; i < numRows; ++i) 
    {
        printf("\n");
        for(int j = 0; j < (i+1); ++j) printf("element %d, %d = %d ", i, j, array2Ddynamic[i][j]);
    }
    // now release all the memory allocated 
    // have to release each row first, then pointer to the row
   for(int i = 0; i < numRows; ++i) 
    {
       free(array2Ddynamic[i]);
    }
    free(array2Ddynamic);
}