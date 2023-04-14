/*
    AVL2.h
    Description: AVL self balancing search tree data structure 
    Author: ######
    SIDNumber: M00741238
    Created: 12.04.2021
    Updated:
*/  

#ifndef AVL2_H
#define AVL2_H

#include <iostream>
#include "Book.h"
#include <iomanip>

struct Node
{
  //storing object as a key comparing will be done by title (string) 
  Book nodeBook;  
  int height;
  Node * parent;
  Node * left;
  Node * right;
};

class AVL
{
  public:
    //root of the binary tree
    Node * root;  
    AVL();
    ~AVL();

    //node operations
    Node * rotationRR(Node * nodeA);
    Node * rotationLL(Node * nodeA);
    Node * rotationRL(Node * nodeA);
    Node * rotationLR(Node * nodeA);
    Node * search(std::string key);
    Node * maxNode(Node * nodeX);
    Node * minNode(Node * nodeX);
    Node * previousNode(Node * nodeX);
    Node * succ(Node * nodeX);
    Node * remove(Node * nodeX);

    //AVL tree general operations
    bool insert(Node * newNode);
    int maxKey(Node * nodeX);
    int minKey(Node * nodeX);
    void preorder(Node * nodeX);
    void inorder(Node * nodeX);
    void postorder(Node * nodeX);
    void print(Node * nodeX);
};

#endif
