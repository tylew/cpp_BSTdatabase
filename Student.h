#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

class Student{
public:
  Student();
  Student(int i_idNum, string i_name, string i_level, string i_major, double i_gpa);
  ~Student();

  string rollbackFormat();
  void setAdvisor(int i_advisor);

  void printInfo();
  int getAdvisor();
  bool hasAdvisor();
  string replaceSpace(string str);
  void removeAdvisor();
  void changeMajor(string i_major);
  string getMajor();


  int idNum;
  string name;
  string level;
  string major;
  double gpa;
  int advisor; //ID num of advisor



};
#endif
