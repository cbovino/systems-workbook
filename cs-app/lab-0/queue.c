/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
I found these exercises on github, this doesnt contain the entire labs. All other labs are coming from 
https://csapp.cs.cmu.edu/3e/labs.html
*/

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/

queue_t *q_new()
{
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    if(queue == NULL){
        return NULL;
    }
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

/* Free all storage used by queue */
void traverse(list_ele_t *q){
    if(q->next != NULL){
        traverse(q->next);
    }
    free(q);
}

void q_free(queue_t *q)
{   
    if(q == NULL){
        return;
    }
    if(q->head != NULL){
        traverse(q->head);
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if(q == NULL && (q = q_new()) == NULL ){
        return false;
    }

    list_ele_t * listItem = malloc(sizeof(list_ele_t));
    if (listItem == NULL) {
        return false;
    }
    listItem->value = malloc(sizeof(int));
    listItem->next = NULL;

    if(listItem->value == NULL){
        free(listItem);
        return false;
    }

    listItem->value = v;
    listItem->next= q->head;

    if(q->head == NULL){
        q->tail = listItem;
    }
    q->head = listItem;
    q->size +=1;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if(q == NULL && (q = q_new()) == NULL ){
        return false;
    }
    list_ele_t * listItem = malloc(sizeof(list_ele_t));
    if(listItem == NULL){
        return false;
    }
    listItem->value =malloc(sizeof(int));
    listItem->next = NULL;

    if(listItem->value == NULL){
        free(listItem);
        return false;
    }

    listItem->value = v;

    if(q->head == NULL){
        q->head = listItem;
        q->tail = listItem;
        return true;
    }
    q->tail->next = listItem;
    q->tail = q->tail->next;
    q->size +=1;
    return true; 

}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
//consider space allocation
bool q_remove_head(queue_t *q, int *vp)
{
    if(q == NULL || q->head == NULL){
        return false;
    }
    if(vp != NULL){
        vp = &q->head->value;
    }
    q->head = q->head->next;
    q->size -=1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */

int q_size(queue_t *q)
{
    if(q == NULL){
        return 0;
    }

    return q->size;
}

/*
  Reverse elements in queue.
  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if(q == NULL || q->head == NULL){
        return;
    }

    list_ele_t * prev = NULL;
    list_ele_t * cur = q->head;
    q->tail = q->head;
    while(cur != NULL){
        list_ele_t *temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }

    q->head = prev;

}