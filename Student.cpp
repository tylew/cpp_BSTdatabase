#include "Student.h"
#define RESET "\033[0m"
#define GREEN "\033[32m"

using namespace std;

Student::Student(){}

Student::Student(int i_idNum, string i_name, string i_level, string i_major, double i_gpa){
  idNum = i_idNum;
  name = replaceSpace(i_name);
  level = replaceSpace(i_level);
  major = replaceSpace(i_major);
  gpa = i_gpa;
  advisor = -1;
}

Student::~Student(){}

void Student::removeAdvisor(){
  advisor = -1;
}

bool Student::hasAdvisor(){
  if (advisor != -1){
    return true;
  }
  return false;
}

void Student::setAdvisor(int i_advisor){
  advisor = i_advisor;
}

int Student::getAdvisor(){
  return advisor;
}

string Student::rollbackFormat(){
  string ret = to_string(idNum) + " " + name  + " " + level + " " + major + " " + to_string(gpa).substr(0,3);
  if(advisor != -1){
    ret += " " + to_string(advisor);
  }
  return ret;
}

void Student::changeMajor(string i_major){
  major = replaceSpace(i_major);
}

string Student::getMajor(){
  return major;
}

void Student::printInfo(){
  cout << GREEN << "\n\e[1mID#" << idNum << "\n\e[0m >" << RESET;
  cout << "Name:    " << name << "\n >";
  cout << "Level:   " << level << "\n >";
  cout << "Major:   " << major << "\n >";
  cout << "GPA:     " << gpa;

  if(advisor != -1){
    cout << "\n >Advisor: " << advisor << endl;
  }else{
    cout << endl;
  }
}

string Student::replaceSpace(string str){
  for (int i = 0; i < str.length(); ++i){
    if (str[i] == ' '){
      str[i] = '-';
    }
  }

  return str;
}
