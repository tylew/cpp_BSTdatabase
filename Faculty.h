#ifndef FACULTY_H
#define FACULTY_H
#include <iostream>
#include "DoublyLinkedList.h"
#include "Student.h"

using namespace std;

class Faculty{
public:
  Faculty();
  Faculty(int i_idNum, string i_name, string i_level, string i_department);
  ~Faculty();

  string toString();
  string replaceSpace(string str);

  int idNum;
  string name;
  string level;
  string department;

  DoublyLinkedList<int>* advisees = new DoublyLinkedList<int>(); //array of advisees of faculty member

  void addAdvisee(int i_stuID);
  int removeAdvisee(int i_stuID);
  DoublyLinkedList<int>* getAdvisees();
  int adviseeCount();
  int getAdvisee(int key);
  bool containsAdvisee(int advisee);
  void printInfo();

  string rollbackFormat();
};
#endif
