#ifndef DoublyLinkedList_H
#define DoublyLinkedList_H

#include <iostream>
using namespace std;

template <typename T>
class ListNode{
  public:
    ListNode();
    ListNode(T d);
    ~ListNode();
    ListNode *next;
    ListNode *prev;
    void setNode(T d);
    T data;
};

//implementation
template <typename T>
ListNode<T>::ListNode(){
  next = NULL;
  prev = NULL;
}

template <typename T>
ListNode<T>::ListNode(T d){
  data = d;
  next = NULL;
  prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  next = NULL;
  prev = NULL;
}

template <typename T>
void ListNode<T>::setNode(T d){
  data = d;
  return;
}

template <typename T>
class DoublyLinkedList{
  public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void insertFront(T d);
    void insertBack(T d);
    T removeFront();
    T removeBack();
    T remove(T key);
    T search(int key);
    int find(T value);
    bool isEmpty();
    bool contains(T value);
    size_t getSize();
    void printList(bool printLink);

    T peekElement(int key);


  private:
    ListNode<T> *front;
    ListNode<T> *back;
    size_t size;

};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
  front = NULL;
  back = NULL;
  size = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
  ListNode<T>* node = front;
  ListNode<T>* nextNode;

  while(node != NULL){
    nextNode = node->next;
    delete node;
    node = nextNode;
  }
}

template <typename T>
bool DoublyLinkedList<T>::contains(T value){
  ListNode<T> *current = front;

  while(current!= 0){

    if(current->data==value){
      return true;
    }else{
      current = current->next;
    }
  }
  return false;
}

template <typename T>
T DoublyLinkedList<T>::peekElement(int key){
  ListNode<T> *current = front;
  
  for(int i = 0; i<key; ++i){
    current = current->next;
  }
  return current->data;
}

template <typename T>
void DoublyLinkedList<T>::insertFront(T d){
  ListNode<T> *node = new ListNode<T>(d);
  if(size == 0){
    back = node;
  }else{
    //list not empty
    node->next = front;
    front->prev = node;
  }
  front = node;
  size++;
}

template <typename T>
void DoublyLinkedList<T>::insertBack(T d){
  ListNode<T> *node = new ListNode<T>(d);
  if(size == 0){
    front = node;
  }else{
    //list not empty
    back->next = node;
    node->prev = back;
  }
  back = node;
  size++;
}

template <typename T>
T DoublyLinkedList<T>::removeFront(){
  if(size == 0){
    throw "Linked list empty, cannot remove front!";
  }
  ListNode<T> *tp = front;

  if(front->next == 0){
      back = 0;
  }else{ //size is >1
    front->next->prev = 0;
  }
  front = front->next;
  tp->next = 0;
  T temp = tp->data;
  size--;
  delete tp;

  return temp;
}

template <typename T>
T DoublyLinkedList<T>::removeBack(){
  if(size == 0){
    throw "Linked list empty, cannot remove back!";
  }
  ListNode<T> *tp = back;

  if(back->prev == 0){ //if size is 1
      front = 0;
  }else{
    back->prev->next = 0;
  }
  back = back->prev;
  tp->prev = 0;
  T temp = tp->data;
  size--;
  delete tp;

  return temp;
}

template <typename T>
T DoublyLinkedList<T>::remove(T key){
  if(size == 0){
    throw "Linked list empty, cannot remove specified key!";
  }
  ListNode<T> *current = front;
  while(current->data!=key){
    current = current -> next;

    if(current == 0){
      throw "Key not contained in list!";
    }
  }
  //found key, so...
  if(current == front){

    return removeFront();
  }if(current == back){

    return removeBack();
  }

  current->prev->next = current->next;
  current->next->prev = current->prev;

  T temp = current->data;
  size--;
  delete current;

  return temp;
}

template <typename T>
int DoublyLinkedList<T>::find(T value){
  int idx = -1;
  ListNode<T> *current = front;

  while(current!= 0){
    ++idx;
    if(current->data==value){
      break;
    }else{
      current = current->next;
    }
  }
  if(current == 0){
    idx = -1;
  }
  return idx;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty(){
  return size == 0;
}

template <typename T>
size_t DoublyLinkedList<T>::getSize(){
  return size;
}

template <typename T>
void DoublyLinkedList<T>::printList(bool printLink){
  ListNode<T> *curr = front;
  while(curr!=0){
    if(curr == front){
      cout << "{FRONT}: ";
    }else if(curr == back){
      cout << "{REAR}: ";
    }if(printLink){
      cout << "[ PREV: "<<curr->prev << " || " << curr->data << " NEXT: " << curr->next << " ] ";
    }else{
      cout << " [ " << curr->data << " ] ";
    }

    curr = curr->next;
    if(curr!=0){
      cout << " ==> ";
    }
  }
  cout << endl;
}

template <typename T>
T DoublyLinkedList<T>::search(int key){
  if(size == 0){
    throw "Linked list empty, cannot access specified key!";
  }
  ListNode<T> *current = front;
  for(int i = 0;i<key;i++){
    current = current -> next;
  }
  return current->data;
}

#endif
