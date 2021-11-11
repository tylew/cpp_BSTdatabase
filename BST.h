#ifndef BST_h
#define BST_h

#include <iostream>
#include <fstream>
#include <string>
#include "Student.h"
#include "Faculty.h"
using namespace std;

template <typename T>
class TreeNode{
public:
  TreeNode();
  TreeNode(int k, T d);
  ~TreeNode();

  T getData();

  int key;
  T data;
  TreeNode<T>* left;
  TreeNode<T>* right;
};

template <typename T>
TreeNode<T>::TreeNode(){
  left = NULL;
  right = NULL;
}

template <typename T>
TreeNode<T>::TreeNode(int k, T d){
  left = NULL;
  right = NULL;
  key = k;
  data = d;
}

template <typename T>
TreeNode<T>::~TreeNode(){
  left = NULL;
  right = NULL;
  key = 0;
  delete data;
}

template <typename T>
T TreeNode<T>::getData(){
  return data;
}

template <typename T>
class BST{
public:
  BST();
  ~BST();

  void insert(int k, T data);
  bool contains(int k); //search function
  bool deleteNode(int k); //returns T/F to determine if successful.
  bool isEmpty();

  T getMin();
  int getMax();

  T getData(); //Returns data stored in placeHolderPointer, which is set by contains()
  T getData(int key); //Only use if key forsure exists

  TreeNode<T>* getSuccessor(TreeNode<T>* d); //plays role in deleteNode()

  void recPrint(TreeNode<T>* node);
  void printTree();
  void destroyRecursive(TreeNode<T>*);

private:
  T placeHolderPointer;
  TreeNode<T>* root;
};

template <typename T>
BST<T>::BST(){
  root = NULL; //empty tree
}

template <typename T>
BST<T>::~BST(){
  destroyRecursive(root);
}

template <typename T>
void BST<T>::destroyRecursive(TreeNode<T>* node){
  if(node){
    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
  }
}

template <typename T>
T BST<T>::getData(){
  //need to check if BST contains key first, if it does it is added to placeHolderPointer type T.
  //DO NOT CALL WITHOUT "contains(int k)" FIRST!!
  return placeHolderPointer;

}

template <typename T>
T BST<T>::getData(int key){
  TreeNode<T>* current = root;
  while(current->key != key){
    if(key < current->key)
       current = current->left;
    else
      current = current->right;
  }

  return current->getData();

}

template <typename T>
void BST<T>::recPrint(TreeNode<T> *node){
  if(node == NULL)
    return;

  recPrint(node->left);
  node->data->printInfo();
  recPrint(node->right);
}

template <typename T>
void BST<T>::printTree(){
  TreeNode<T>* node = root;
  if(node == NULL){
    cout << "\n\n\n\n\n\nNothing to see here...\n";
    return;
  }

  recPrint(node->left);
  node->data->printInfo();
  recPrint(node->right);
}

template <typename T>
T BST<T>::getMin(){
  if(root == NULL)
    return NULL;

  TreeNode<T>* current = root;

  while(current->left != NULL){
    current = current->left;
  }

  return current->data;

}

template <typename T>
int BST<T>::getMax(){
  if(root == NULL)
    return NULL;

  TreeNode<T>* current = root;

  while(current->right != NULL){
    current = current->right;
  }

  return current->key;
}

template <typename T>
void BST<T>::insert(int key, T data){

  TreeNode<T>* node = new TreeNode<T>(key, data);

  if(isEmpty()){
    root = node;
    return;
  }

  //tree not empty, need to find insertion point
  TreeNode<T>* current = root;
  TreeNode<T>* parent = NULL;


  while(true){
    parent = current;
    if(key < current->key){ // go left
      current = current->left;

      if(current == NULL){ //found insertion point
        parent->left = node;
        break;
      }

    }else{//go right
      current = current->right;

      if(current == NULL){
        parent->right = node;
        break;
      }

    }

  }
}

template <typename T>
bool BST<T>::contains(int value){ //TEMPLATE
  if(isEmpty()){
    return false;
  }else{
    TreeNode<T>* current = root;
    while(current->key != value){
      if(value < current->key)
         current = current->left;
      else
        current = current->right;
      if(current == NULL){
        return false;
      }
    }

    placeHolderPointer = current->getData(); //data from key found stored for use in getPointer()
    return true;
  }
}

template <typename T>
bool BST<T>::isEmpty(){
  return (root == NULL);
}

template <typename T>
bool BST<T>::deleteNode(int k){
  if(isEmpty()||!contains(k)){
    return false;
  }
  TreeNode<T>* node_delete = NULL;
  TreeNode<T>* parent = NULL;
  TreeNode<T>* current = root;
  bool isLeftNode;

  while(current->key != k){
    parent = current;

    if(k < current->key){ //If key being deleted is less than current key move to left
      isLeftNode = true;
      current = current->left;
    }else{ //Moves to right
      isLeftNode = false;
      current = current->right;
    }if(current == NULL){ //Reached end of tree, should never reach this point though
      return false;
    }
  }
  //found key, proceed to delete node.
  node_delete = current;
  //case 1: leaf node, no children
  if(current->left == NULL && current->right == NULL){
    if(current==root){
      root = NULL;
    }else if(isLeftNode){
      parent->left = NULL;
    }else{
      parent->right = NULL;
    }
  }
  //case 2: Node being deleted has single children
  else if(current->right == NULL){ //Know 1 node is not null, so left node must contain value
    if(current == root){
      root = current->left;
    }else if(isLeftNode){
      parent->left = current->left;
    }else{
      parent->right = current->left;
    }
  }

  else if(current->left == NULL){ //Left node null, so right node must contain value
    if(current == root){
      root = current->right;
    }else if(isLeftNode){
      parent->left = current->right;
    }else{
      parent->right = current->right;
    }
  }
  //case 3: node deleted has two children
  else{
    TreeNode<T>* successor = getSuccessor(current);

    if(current == root){
      root = successor;
    }else if(isLeftNode){
      parent->left = successor;
    }else{
      parent->right = successor;
    }

    successor->left = current->left;

  }

  delete node_delete;
  return true;
}

template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d){
  TreeNode<T>* sp = d;
  TreeNode<T>* successor = d;
  TreeNode<T>* current = d->right;

  while(current != NULL){
    sp = successor;
    successor = current;
    current = current->left;
  }

  if(successor != d->right){
    sp->left = successor->right;
    successor->right = d->right;
  }

  return successor;
}



#endif
