#include "delist.h"
#include <iostream>

// Constructs an empty Double-Ended List
DEList::DEList(){
    frontNode = NULL;
    backNode = NULL;
}
// Destructor to clean-up memory of current list
DEList::~DEList(){
    while (frontNode != NULL) {
        DEItem *next = frontNode->next;
        delete frontNode;
        frontNode = next;
    }
}
// returns a Boolean 'true' if the list is empty
bool DEList::empty(){
    return (frontNode == NULL && backNode == NULL);
}
// returns number of items in the list
int DEList::size(){
    int size = 0;
    DEItem *current = frontNode;
    while (current != NULL) {
        current = current->next;
        size++;
    }
    return size;
}
// returns front item or -1 if empty list
int DEList::front(){
    if (frontNode == NULL) 
        return -1;
    return (frontNode->val);
}
// returns back item or -1 if empty list
int DEList::back(){
    if (backNode == NULL)
        return -1;
    return (backNode->val);
}
// Adds a new integer to the front of the list
void DEList::push_front(int new_val){
    //Creates new node
    DEItem *newNode = new DEItem();
    newNode->val = new_val;


    //Checks if list is empty
    if (empty()) {
        frontNode = newNode;
        backNode = newNode;
        newNode -> next = NULL;
        newNode -> prev = NULL;
        return;
    } 

    //Adds node to front
    newNode->prev = NULL;
    newNode->next = frontNode;
    frontNode->prev = newNode;
    frontNode = newNode;
}
// Adds a new integer to the back of the list
void DEList::push_back(int new_val){
    //Creates new node
    DEItem *newNode = new DEItem();
    newNode->val = new_val;

    //Puts node in if list is empty
    if (empty()) {
        frontNode = newNode;
        backNode = newNode;
        newNode -> next = NULL;
        newNode -> prev = NULL;
        return;
    }

    //Adds node to back
    newNode->next = NULL;
    newNode->prev = backNode;
    backNode->next = newNode;
    backNode = newNode;
}
// Removes the front item of the list (if it exists)
void DEList::pop_front(){
    if (empty()) 
        return;

    //Stores oldFrontNode into variable
    DEItem* oldFrontNode = frontNode;

    //Removes item from list
    frontNode = frontNode->next;

    if (frontNode == NULL) 
        backNode = NULL;
    else
        frontNode->prev = NULL;

    //Deletes old node
    delete oldFrontNode;
}
// Removes the back item of the list (if it exists)
void DEList::pop_back(){
    if (empty()) 
        return;

    //Stores oldBackNode into variable
    DEItem* oldBackNode = backNode;

    //Removes item from list
    backNode = backNode->prev;

    if (backNode == NULL) 
        frontNode = NULL;
    else 
        backNode->next = NULL;

    //Deletes oldBackNode
    delete oldBackNode;
}