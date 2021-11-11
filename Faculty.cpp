#include "Faculty.h"
#define RESET "\033[0m"
#define GREEN "\033[32m"

using namespace std;

Faculty::Faculty(){}

Faculty::Faculty(int i_idNum, string i_name, string i_level, string i_department){
  idNum = i_idNum;
  name = replaceSpace(i_name);
  level = replaceSpace(i_level);
  department = replaceSpace(i_department);
}

Faculty::~Faculty(){
  delete advisees;
}

void Faculty::addAdvisee(int i_stuID){
  advisees->insertFront(i_stuID);
}

DoublyLinkedList<int>* Faculty::getAdvisees(){
  return advisees;
}

bool Faculty::containsAdvisee(int advisee){
  if(advisees->contains(advisee)){
    return true;
  }
  return false;
}

int Faculty::adviseeCount(){

  return advisees->getSize();
}

int Faculty::getAdvisee(int key){
  return advisees->peekElement(key);
}

string Faculty::rollbackFormat(){
  string ret = to_string(idNum) + " " + name  + " " + level + " " + department;
  for(int i = 0;i<advisees->getSize();++i){
    ret += " " + to_string(advisees->peekElement(i));
  }
  return ret;
}

int Faculty::removeAdvisee(int i_stuID){
  int remID;
  if(advisees->contains(i_stuID)){
    remID = advisees->remove(i_stuID);

    return remID;
  }
  return 0;
}

void Faculty::printInfo(){
  cout << GREEN << "\n\e[1mID#" << idNum << "\n\e[0m" << RESET;
  cout << " >Name:       " << name << endl;
  cout << " >Level:      " << level << endl;
  cout << " >Department: " << department << endl;
  if(!(advisees->isEmpty())){
    for(int i = 0;i < advisees->getSize(); ++i){
      cout << " >Advisee #" << i+1 << ": " << advisees->peekElement(i) << endl;
    }
  }
}

string Faculty::replaceSpace(string str){
  for (int i = 0; i < str.length(); ++i){
    if (str[i] == ' '){
      str[i] = '-';
    }
  }

  return str;
}
