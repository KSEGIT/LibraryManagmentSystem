/*
    AVL2.cpp
    Description: AVL self balancing search tree data structure 
    Author: ######
    SIDNumber: M00741238
    Created: 12.04.2021
    Updated:
*/

#include "AVL2.h"

// constructor
AVL::AVL()
{
  root = nullptr;
}
// destructor
AVL::~AVL()
{
  //while(root)
  delete (remove(root));
}

// RR rotation
Node *AVL::rotationRR(Node *nodeA)
{
  Node *nodeB = nodeA->right;
  Node *nodeParent = nodeA->parent;

  nodeA->right = nodeB->left;
  if (nodeA->right)
    nodeA->right->parent = nodeA;
  nodeB->left = nodeA;
  nodeB->parent = nodeParent;
  nodeA->parent = nodeB;
  if (nodeParent)
  {
    if (nodeParent->left == nodeA)
      nodeParent->left = nodeB;
    else
      nodeParent->right = nodeB;
  }
  else
    root = nodeB;

  if (nodeB->height == -1)
  {
    nodeA->height = nodeB->height = 0;
  }
  else
  {
    nodeA->height = -1;
    nodeB->height = 1;
  }
  return nodeB;
}

// LL rotation
Node *AVL::rotationLL(Node *nodeA)
{
  Node *nodeB = nodeA->left;
  Node *nodeParent = nodeA->parent;

  nodeA->left = nodeB->right;
  if (nodeA->left)
    nodeA->left->parent = nodeA;
  nodeB->right = nodeA;
  nodeB->parent = nodeParent;
  nodeA->parent = nodeB;
  if (nodeParent)
  {
    if (nodeParent->left == nodeA)
      nodeParent->left = nodeB;
    else
      nodeParent->right = nodeB;
  }
  else
    root = nodeB;

  if (nodeB->height == 1)
  {
    nodeA->height = nodeB->height = 0;
  }
  else
  {
    nodeA->height = 1;
    nodeB->height = -1;
  }
  return nodeB;
}

// RL rotation
Node *AVL::rotationRL(Node *nodeA)
{
  Node *nodeB = nodeA->right, *nodeC = nodeB->left, *nodeParent = nodeA->parent;
  nodeB->left = nodeC->right;
  if (nodeB->left)
    nodeB->left->parent = nodeB;
  nodeA->right = nodeC->left;
  if (nodeA->right)
    nodeA->right->parent = nodeA;
  nodeC->left = nodeA;
  nodeC->right = nodeB;
  nodeA->parent = nodeB->parent = nodeC;
  nodeC->parent = nodeParent;
  if (nodeParent)
  {
    if (nodeParent->left == nodeA)
      nodeParent->left = nodeC;
    else
      nodeParent->right = nodeC;
  }
  else
    root = nodeC;
  nodeA->height = (nodeC->height == -1) ? 1 : 0;
  nodeB->height = (nodeC->height == 1) ? -1 : 0;
  nodeC->height = 0;
  return nodeC;
}

// LR Rotation
Node *AVL::rotationLR(Node *nodeA)
{
  Node *nodeB = nodeA->left, *nodeC = nodeB->right, *nodeParent = nodeA->parent;

  nodeB->right = nodeC->left;
  if (nodeB->right)
    nodeB->right->parent = nodeB;
  nodeA->left = nodeC->right;
  if (nodeA->left)
    nodeA->left->parent = nodeA;
  nodeC->right = nodeA;
  nodeC->left = nodeB;
  nodeA->parent = nodeB->parent = nodeC;
  nodeC->parent = nodeParent;
  if (nodeParent)
  {
    if (nodeParent->left == nodeA)
    {
      nodeParent->left = nodeC;
    }
    else
      nodeParent->right = nodeC;
  }
  else
    root = nodeC;

  nodeA->height = (nodeC->height == 1) ? -1 : 0;
  nodeB->height = (nodeC->height == -1) ? 1 : 0;
  nodeC->height = 0;

  return nodeC;
}

//insert new node to tree
bool AVL::insert(Node *newNode)
{
  //top node
  Node *nodeX = root;
  Node *nodeY;
  Node *nodeZ;

  nodeY = newNode->left = newNode->right = nullptr;
  newNode->height = 0;

  while (nodeX)
  {
    if (nodeX->nodeBook == newNode->nodeBook)
    {
      delete newNode;
      return false;
    }
    nodeY = nodeX;
    nodeX = (newNode->nodeBook < nodeX->nodeBook) ? nodeX->left : nodeX->right;
  }

  if (!(newNode->parent = nodeY))
  {
    root = newNode;
    return true;
  }
  if (newNode->nodeBook < nodeY->nodeBook)
    nodeY->left = newNode;
  else
    nodeY->right = newNode;
  if (nodeY->height)
  {
    nodeY->height = 0;
    return true;
  }
  nodeY->height = (nodeY->left == newNode) ? 1 : -1;
  nodeZ = nodeY->parent;
  while (nodeZ)
  {
    if (nodeZ->height)
      break;
    nodeZ->height = (nodeZ->left == nodeY) ? 1 : -1;
    nodeY = nodeZ;
    nodeZ = nodeZ->parent;
  }
  if (!nodeZ)
    return true;
  if (nodeZ->height == 1)
  {
    if (nodeZ->right == nodeY)
    {
      nodeZ->height = 0;
      return true;
    }
    if (nodeY->height == -1)
      rotationLR(nodeZ);
    else
      rotationLL(nodeZ);
    return true;
  }
  else
  {
    if (nodeZ->left == nodeY)
    {
      nodeZ->height = 0;
      return true;
    }
    if (nodeY->height == 1)
      rotationRL(nodeZ);
    else
      rotationRR(nodeZ);
    return true;
  }
}

//searching by string key
Node *AVL::search(std::string key)
{
  //starting at root
  Node *nodeX = root;
  //todo check access and find bug depending on whitespaces
  while ((nodeX) && (nodeX->nodeBook.getTitle() != key))
    nodeX = (key < nodeX->nodeBook.getTitle()) ? nodeX->left : nodeX->right;
  return nodeX;
}

//node with min key
Node *AVL::maxNode(Node *nodeX)
{
  while (nodeX->right)
    nodeX = nodeX->right;
  return nodeX;
}

// returns previous node
Node *AVL::previousNode(Node *nodeX)
{
  if (nodeX->left)
    return maxNode(nodeX->left);
  Node *nodeY;
  do
  {
    nodeY = nodeX;
    nodeX = nodeX->parent;
  } while (nodeX && (nodeX->right != nodeY));
  return nodeX;
}

//removing node from the tree
Node *AVL::remove(Node *nodeX)
{
  Node *t, *nodeY, *nodeZ;
  bool nest;

  if ((nodeX->left) && (nodeX->right))
  {
    nodeY = remove(previousNode(nodeX));
    nest = false;
  }
  else
  {
    if (nodeX->left)
    {
      nodeY = nodeX->left;
      nodeX->left = nullptr;
    }
    else
    {
      nodeY = nodeX->right;
      nodeX->right = nullptr;
    }
    nodeX->height = 0;
    nest = true;
  }

  if (nodeY)
  {
    nodeY->parent = nodeX->parent;
    if (nodeY->left == nodeX->left)
      nodeY->left->parent = nodeY;
    if (nodeY->right == nodeX->right)
      nodeY->right->parent = nodeY;
    nodeY->height = nodeX->height;
  }

  if (nodeX->parent)
  {
    if (nodeX->parent->left == nodeX)
      nodeX->parent->left = nodeY;
    else
      nodeX->parent->right = nodeY;
  }
  else
    root = nodeY;

  if (nest)
  {
    nodeZ = nodeY;
    nodeY = nodeX->parent;
    while (nodeY)
    {
      if (!(nodeY->height))
      {
        // case1
        nodeY->height = (nodeY->left == nodeZ) ? -1 : 1;
        break;
      }
      else
      {
        if (((nodeY->height == 1) && (nodeY->left == nodeZ)) || ((nodeY->height == -1) && (nodeY->right == nodeZ)))
        {
          // case2
          nodeY->height = 0;
          nodeZ = nodeY;
          nodeY = nodeY->parent;
        }
        else
        {
          t = (nodeY->left == nodeZ) ? nodeY->right : nodeY->left;
          if (!(t->height))
          {
            // case3
            if (nodeY->height == 1)
              rotationLL(nodeY);
            else
              rotationRR(nodeY);
            break;
          }
          else if (nodeY->height == t->height)
          {
            // case4
            if (nodeY->height == 1)
              rotationLL(nodeY);
            else
              rotationRR(nodeY);
            nodeZ = t;
            nodeY = t->parent;
          }
          else
          {
            // case5
            if (nodeY->height == 1)
              rotationLR(nodeY);
            else
              rotationRL(nodeY);
            nodeZ = nodeY->parent;
            nodeY = nodeZ->parent;
          }
        }
      }
    }
  }
  return nodeX;
}

//printintg tree - testing visualy:P
void AVL::print(Node *nodeX)
{
  std::cout << nodeX->nodeBook.getTitle() << " | height = " << " | " << nodeX->height << " : Left-> ";
  if (nodeX->left)
    std::cout << " | " << nodeX->left->nodeBook.getTitle();
  else
    std::cout << "null";
  std::cout << "| Right-> ";
  if (nodeX->right)
    std::cout << " | " << nodeX->right->nodeBook.getTitle();
  else
    std::cout << "null";
  std::cout << " : parent -> ";
  if (nodeX->parent)
    std::cout << " | " << nodeX->parent->nodeBook.getTitle();
  else
    std::cout << "null";
  std::cout << std::endl;
  if (nodeX->left)
    print(nodeX->left);
  if (nodeX->right)
    print(nodeX->right);
}
