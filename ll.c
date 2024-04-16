#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create() {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    return l;
}

bool list_add(LL *l, item *i) {
    //allocate memory for new node
    Node *n = (Node *) malloc(sizeof(Node));

    //check if memory allocation was successful
    if (n == NULL) {

        return false; //return false if allocation failed
    }

    //set the data of the new node to the input item
    n->data = *i;

    //set the next pointer of the new node to NULL
    n->next = NULL;

    //check if linked list is empty
    if (l->head == NULL) {

        //if the list is empty, set the head of the list to the new node
        l->head = n;
        l->tail = n;
    } else {
        //if the list is not empty, traverse to the end to find the tail
        /*Node *tail = l->head;
		while (tail->next != NULL) {
			tail = tail->next;
		}*/
        //set the next pointer of the tail to the new mode
        Node *temp = l->tail;
        temp->next = n;
        l->tail = n;
    }
    return true;
}

item *list_find(LL *l, bool (*cmp)(item *, item *), item *i) {
    //start at the head of the linked list
    Node *n = l->head;

    //traverse list
    while (n != NULL) {
        //use cmp function to compare data of current node with target item
        if (cmp(&n->data, i)) {
            //if found, return pointer
            return &n->data;
        }
        //move to next node
        n = n->next;
    }
    //if not found return NULL
    return NULL;
}

void list_remove(LL *l, bool (*cmp)(item *, item *), item *i) {
    if (l == NULL || l->head == NULL) {
        return;
    }

    Node *current = l->head;
    Node *prev = NULL;

    if (cmp(&current->data, i)) {
        l->head = current->next;

        if (current->next == NULL) {
            l->tail = NULL;
        }

        free(current);
        return;
    }

    while (current != NULL) {
        if (cmp(&current->data, i)) {
            if (prev != NULL) {
                prev->next = current->next;
                if ((current->next) == NULL) {
                    l->tail = prev;
                }
            }

            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void list_destroy(LL **l_ptr) {

    if (l_ptr == NULL || *l_ptr == NULL) {
        return;
    }
    Node *current = (*l_ptr)->head;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(*l_ptr);
    *l_ptr = NULL;
}
