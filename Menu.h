#ifndef MENU_H
#define MENU_H
#include "Student.h"
#include "Faculty.h"
#include "BST.h"
#include "DoublyLinkedList.h"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#include <iostream>
#include <fstream>

using namespace std;

class Menu{
public:
  Menu();
  ~Menu();

  void displayChoices();
  void readFromFile();

private:
  BST<Student*>* studentTree = new BST<Student*>(); //when creating BST, type 1 is student, 2 is faculty
  BST<Faculty*>* facultyTree = new BST<Faculty*>();

  DoublyLinkedList<string>* rollback = new DoublyLinkedList<string>();

  void deleteStudent(int i_idNum, bool rollbackBool);
  void deleteFaculty(int i_idNum, bool rollbackBool);

  void saveToFiles();
  void changeStudentMajor(int stuID, string newMajor, bool rb);


};
#endif
