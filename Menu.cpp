#include "Menu.h"

using namespace std;

Menu::Menu(){

  readFromFile();

  //facultyTree->insert(454, new Faculty(454, "Craig", "Director", "Clean Coalition"));

  int choice;
  string ph_choice;

  while(choice != 14){

      displayChoices();
      cout << " --> ";
      try{ //get user input
        getline(cin,ph_choice);
        choice = stoi(ph_choice);
      }catch(invalid_argument& e){
        choice = 16;
        cout << endl;
      }

      if(choice == 1){ //print student tree
        studentTree->printTree();
      }else if(choice == 2){ //print faculty tree
        facultyTree->printTree();
      }else if(choice == 3){ //Display info on student by ID
        cout << "What is the ID number of the student you want to view?\n --> ";
        int i_idNum;
        try{ //get user input
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);

          if(studentTree->contains(i_idNum)){
            studentTree->getData()->printInfo();
          }else{
            cout << "Student with ID #" << i_idNum << " does not exist." << endl;
          }
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 4){ //Display info on faculty by ID
        int i_idNum;
        try{
          cout << "What is the ID number of the faculty you want to view?\n --> ";
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);

          if(facultyTree->contains(i_idNum)){
            facultyTree->getData()->printInfo();
          }else{
            cout << "Faculty with ID #" << i_idNum << " does not exist." << endl;
          }
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 5){ //Display student advisor info
        int i_idNum;
        try{
          cout << "What is the student ID# who's advisor file you want to view?" << endl;
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);

          if(studentTree->contains(i_idNum)){
            if(studentTree->getData()->hasAdvisor()){
              facultyTree->getData(studentTree->getData()->getAdvisor())->printInfo();
            }else{
              cout << "Student with specified ID# does not have an advisor." << endl;
            }
          }else{
            cout << "Student with specified ID# does not exist." << endl;
          }
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 6){ //Display faculty advisee info
        int i_idNum;
        try{
          cout << "What is the faculty ID# who's advisee files you want to view?" << endl;
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);

          if(facultyTree->contains(i_idNum)){
            DoublyLinkedList<int>* facViseeslmao = facultyTree->getData()->getAdvisees();
            int ph_ID;
            if(facViseeslmao->getSize()==0){
              cout << "Faculty with specified ID# does not have an advisee." << endl;
            }else{
              for(int i = 0;i<facViseeslmao->getSize();++i){
                ph_ID = facViseeslmao->peekElement(i);
                if(studentTree->contains(ph_ID)){
                  studentTree->getData()->printInfo();
                }
              }
            }
          }else{
            cout << "Faculty with specified ID# does not exist." << endl;
          }
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 7){ //add new student, include rollback addition
        int i_idNum;
        string i_name;
        string i_level;
        string i_major;
        double i_gpa;
        try{
          cout << "What is the ID number of the student you would like to add?\n --> ";
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);

          cout << "\nWhat is the name of the student you would like to add?\n --> ";
          getline(cin,i_name);

          cout << "\nWhat is the level of the student you would like to add?\n --> ";
          getline(cin,i_level);

          cout << "\nWhat is the major of the student you would like to add?\n --> ";
          getline(cin,i_major);

          cout << "\nWhat is the GPA of the student you would like to add?\n --> ";
          getline(cin,ph_choice);
          i_gpa = stod(ph_choice);

          studentTree->insert(i_idNum, new Student(i_idNum,i_name,i_level,i_major,i_gpa));
          rollback->insertFront("deleteStu " + to_string(i_idNum)); //Queue rollback command

          cout << endl << "\nPlease choose option 11 to add an advisor to student " << GREEN << "ID#" << i_idNum << RESET;
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 8){ //Delete student given ID, adjust advisor to match
        int i_idNum;
        try{
          cout << "What is the ID number of the student you would like to delete? \n --> ";
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);

          deleteStudent(i_idNum, true);
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 9){ //Add new faculty member
        int i_idNum;
        string i_name;
        string i_level;
        string i_department;
        try{
          cout << "What is the ID number of the facultyTree you would like to add?\n --> ";
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);

          cout << "\nWhat is the name of the faculty you would like to add?\n --> ";
          getline(cin,i_name);

          cout << "\nWhat is the level of the faculty you would like to add?\n --> ";
          getline(cin,i_level);

          cout << "\nWhat is the department of the faculty you would like to add?\n --> ";
          getline(cin,i_department);

          facultyTree->insert(i_idNum, new Faculty(i_idNum,i_name,i_level,i_department));
          rollback->insertFront("deleteFac " + to_string(i_idNum)); //Queue rollback command

          cout << endl << "\nPlease choose option 11 to add advisees to faculty " << GREEN << "ID#" << i_idNum << RESET;
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 10){ //Remove faculty member, remove advisor of advisees
        try{
          int i_idNum;
          cout << "What is the ID number of the faculty you would like to delete? \n --> ";
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);

          deleteFaculty(i_idNum, true);
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 11){ //Change student advisor
        try{
          int stu_idNum;
          cout << "What is the student ID# who's advisor you want to set? \n --> ";
          getline(cin,ph_choice);
          stu_idNum = stoi(ph_choice);
          if(studentTree->contains(stu_idNum)){
            int fac_idNum;
            cout << "What is the advisor faculty ID#? \n --> ";
            getline(cin,ph_choice);
            fac_idNum = stoi(ph_choice);
            if(facultyTree->contains(fac_idNum)){
              int oldAdvisor;
              oldAdvisor = studentTree->getData()->getAdvisor();

              studentTree->getData()->setAdvisor(fac_idNum);
              facultyTree->getData()->addAdvisee(stu_idNum);
              cout << "Student " << GREEN << "ID#" << stu_idNum << RESET << " is now advised by faculty " << GREEN << "ID#" << fac_idNum <<RESET <<endl;

              rollback->insertFront("cngStuAdv " + to_string(stu_idNum) + " " + to_string(oldAdvisor));
            }else{
              cout << "Faculty with ID#" << stu_idNum << " does not exist, cannot set as advisor." << endl;
            }
          }else{
            cout << "Student with ID#" << stu_idNum << " does not exist." << endl;
          }
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 12){ //Remove faculty advisee
        try{
          cout << "What is the ID# of the faculty you wish to remove an advisee? \n --> ";
          int i_idNum;
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);
          if(facultyTree->contains(i_idNum)){
            if(facultyTree->getData()->adviseeCount()>0){
              cout << "What is the ID# of the advisee you wish to remove? \n --> ";
              int stu_idNum;
              getline(cin,ph_choice);
              stu_idNum = stoi(ph_choice);

              if(facultyTree->getData()->containsAdvisee(stu_idNum)&&studentTree->contains(stu_idNum)){
                facultyTree->getData()->removeAdvisee(stu_idNum);
                studentTree->getData()->removeAdvisor();
                cout << "Faculty " << GREEN << "ID#" << i_idNum << RESET << " successfully removed advisee of " <<GREEN << "ID#" << stu_idNum << RESET << endl;
                rollback->insertFront("addAdv " + to_string(i_idNum) + " " + to_string(stu_idNum));
              }else{
                cout << "Specified faculty does not contain specified advisee." << endl;
              }
            }else{
              cout << "Specified faculty has no advisees." << endl;
            }
          }else{
            cout << "Faculty with specified ID# does not exist." << endl;
          }
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else if(choice == 13 && !(rollback->isEmpty())){ //ROLLLBACKMOTHERFUCKKAH -> infinite rollback, only 5 is 4 little boys
        string curr_rollback = rollback->removeFront();
        string ph_rollback = "";
        string rbType = "";

        for(int i=0;i<curr_rollback.size();++i){ //Get rollback type
          if(curr_rollback[i]==' '){ //hit space
            rbType = ph_rollback;
            break;
          }
          ph_rollback = ph_rollback + curr_rollback[i];
        }

        if(rbType == "deleteStu"){
          ph_rollback = "";
          for(int i=10;i<curr_rollback.size();++i){ //Get ID num
            ph_rollback = ph_rollback + curr_rollback[i];
          }
          deleteStudent(stoi(ph_rollback), false);
        }else if(rbType == "addStu"){ //Add back student
          ph_rollback = "";
          int i_idNum = 0;
          string i_name = "";
          string i_level = "";
          string i_major = "";
          double i_gpa = 0.0;
          int i_advisor = 0;

          for(int i=7;i<curr_rollback.size();++i){
            if(curr_rollback[i]==' '){
              if(i_idNum == 0){
                i_idNum = stoi(ph_rollback);
                ph_rollback = "";
              }else if(i_name == ""){
                i_name = ph_rollback;
                ph_rollback = "";
              }else if(i_level == ""){
                i_level = ph_rollback;
                ph_rollback = "";
              }else if(i_major == ""){
                i_major = ph_rollback;
                ph_rollback = "";
              }else if(i_gpa == 0.0){
                i_gpa = stod(ph_rollback);
                ph_rollback = "";
              }
            }else{
              ph_rollback = ph_rollback + curr_rollback[i];
            }
          }
          if(ph_rollback.size()>0){
            i_advisor = stoi(ph_rollback);
          }


          studentTree->insert(i_idNum, new Student(i_idNum,i_name,i_level,i_major,i_gpa));

          cout << "Student " << GREEN << "ID#" << i_idNum << RESET << " was added back to database";

          if(facultyTree->contains(i_advisor)){
            studentTree->getData(i_idNum)->setAdvisor(i_advisor);
            facultyTree->getData()->addAdvisee(i_idNum);
            cout << ", and assigned advisor " <<GREEN<<"ID#" <<i_advisor <<RESET;
          }

          cout << "." << endl;;

        }else if(rbType == "deleteFac"){ //Delete newly added faculty
          ph_rollback = "";
          for(int i=10;i<curr_rollback.size();++i){ //Get ID num
            ph_rollback = ph_rollback + curr_rollback[i];
          }
          deleteFaculty(stoi(ph_rollback), false);
        }else if(rbType == "addFac"){ //Add back deleted faculty
          ph_rollback = "";
          int i_idNum = 0;
          string i_name = "";
          string i_level = "";
          string i_department = "";
          int i_advisee = 0;

          for(int i=7;i<curr_rollback.size();++i){
            if(curr_rollback[i]==' '){
              if(i_idNum == 0){
                i_idNum = stoi(ph_rollback);
                ph_rollback = "";
              }else if(i_name == ""){
                i_name = ph_rollback;
                ph_rollback = "";
              }else if(i_level == ""){
                i_level = ph_rollback;
                ph_rollback = "";
              }else if(i_department == ""){
                i_department = ph_rollback;
                ph_rollback = "";
              }else{
                ph_rollback = ph_rollback + curr_rollback[i];
              }
            }else{
              ph_rollback = ph_rollback + curr_rollback[i];
            }
          }

          if(i_department == ""){ //For faculty without advisees
            i_department = ph_rollback;
            ph_rollback = "";
          }


          facultyTree->insert(i_idNum, new Faculty(i_idNum,i_name,i_level,i_department));

          cout << "Faculty " << GREEN << "ID#" << i_idNum << RESET << " was added back to database." << endl;

          string placehold_ID = "";
          if(ph_rollback.size()>0){
            for(int i = 0; i<ph_rollback.size();++i){
              if(ph_rollback[i]==' '){

                facultyTree->getData(i_idNum)->addAdvisee(stoi(placehold_ID));
                studentTree->getData(stoi(placehold_ID))->setAdvisor(i_idNum);
                cout << "and assigned advisee " <<GREEN<<"ID#" << placehold_ID <<RESET <<endl;
                placehold_ID = "";
              }else{
                placehold_ID = placehold_ID + ph_rollback[i];
              }
            }

            facultyTree->getData(i_idNum)->addAdvisee(stoi(placehold_ID));
            studentTree->getData(stoi(placehold_ID))->setAdvisor(i_idNum);
            cout << "and assigned advisee " <<GREEN<<"ID#" << placehold_ID <<RESET<<endl;
         }


        }else if(rbType == "cngStuAdv"){ //Revert student advisor
          int stu_idNum;
          int old_advisor;
          string ph_itterator = "";

          for(int i = 10;i<curr_rollback.size();++i){
            if(curr_rollback[i]==' '){
              stu_idNum = stoi(ph_itterator);
              ph_itterator = "";
            }
            ph_itterator = ph_itterator + curr_rollback[i];
          }
          old_advisor = stoi(ph_itterator);

          if(facultyTree->contains(studentTree->getData(stu_idNum)->getAdvisor())){
            facultyTree->getData()->removeAdvisee(stu_idNum);
            studentTree->getData(stu_idNum)->setAdvisor(old_advisor);
            cout << "Student " << GREEN << "ID#" << stu_idNum << RESET << " rolled back addition of advisor";
            if(old_advisor!= -1){
              facultyTree->getData(old_advisor)->addAdvisee(stu_idNum);
              cout << " to their previous advisor " << GREEN << "ID#" << old_advisor;
            }

            cout << "." << endl;

          }else{
            cout << "Error rollbacking student advisors" <<endl;
          }

        }else if(rbType == "addAdv"){ //Add removed advisor
          int fac_idNum;
          int old_advisee;
          string ph_itterator = "";

          for(int i = 7;i<curr_rollback.size();++i){
            if(curr_rollback[i]==' '){
              fac_idNum = stoi(ph_itterator);
              ph_itterator = "";
            }
            ph_itterator = ph_itterator + curr_rollback[i];
          }
          old_advisee = stoi(ph_itterator);

          facultyTree->getData(fac_idNum)->addAdvisee(old_advisee);
          studentTree->getData(old_advisee)->setAdvisor(fac_idNum);

          cout << "\nReinstated student " << GREEN << "ID#" << old_advisee << RESET << " as advisee of faculty " <<GREEN << "ID#" << fac_idNum << RESET << endl;
        }else if(rbType == "cngMajor"){
          int stu_idNum;
          string oldMajor;
          ph_rollback = "";
          for(int i=9;i<curr_rollback.size();++i){
            if(curr_rollback[i]==' '){
              stu_idNum = stoi(ph_rollback);
              ph_rollback = "";
            }else{
              ph_rollback = ph_rollback + curr_rollback[i];
            }
          }
          oldMajor = ph_rollback;
          changeStudentMajor(stu_idNum,oldMajor, true);
        }else{ //error
            cout << "\nExperienced fatal error in rollback." << endl;
        }
      }else if(choice == 13){ //If rollback called with nothing to rollback on
          cout << "\nNothing to roll back!" << endl;
      }else if(choice == 14){
          cout << "\nExiting program and saving to master files..." << endl;

      }else if(choice == 15){
        int i_idNum;
        try{
          cout << "\nWhat is the ID number of the student you would like to change majors? \n --> ";
          getline(cin,ph_choice);
          i_idNum = stoi(ph_choice);
          if(studentTree->contains(i_idNum)){
            cout << "\nWhat is the new major of this student? \n --> ";
            getline(cin,ph_choice);
            changeStudentMajor(i_idNum,ph_choice, false);
          }else{
            cout << "\nStudent with specified ID# does not exist. " << endl;
          }
        }catch(invalid_argument& e){
          cout << "\nError: Must enter a number.";
        }
      }else{
        cout << "\nNot a valid choice" << endl;
      }

      if(choice != 14){
      cout << "\nPress ENTER to continue..." << endl;

        //rollback->printList(false);
        cin.ignore();
      }
  }
}

Menu::~Menu(){
  saveToFiles();

  delete studentTree;
  delete facultyTree;
  delete rollback;

  cout<<"Goodbye." << endl;
}

void Menu::saveToFiles(){
  ofstream studentFile("masterStudent.txt");
  ofstream facultyFile("masterFaculty.txt");
  ofstream rollbackFile("masterRollback.txt");
  studentFile << "";
  while(!(studentTree->isEmpty())){
    studentFile << studentTree->getMin()->rollbackFormat() << "\n";
    studentTree->deleteNode(studentTree->getMin()->idNum);
  }
  while(!(facultyTree->isEmpty())){
    facultyFile << facultyTree->getMin()->rollbackFormat() << "\n";
    facultyTree->deleteNode(facultyTree->getMin()->idNum);
  }
  studentFile.close();
  facultyFile.close();
  while(!(rollback->isEmpty())){
    rollbackFile << rollback->removeFront();
    if(rollback->getSize()>=1){
      rollbackFile << "\n";
    }
  }
  rollbackFile.close();
}

void Menu::displayChoices(){
  cout << "\n1. Print all students and their information (sorted by ascending id #)" << endl;
  cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
  cout << "3. Find and display student information given the students id" << endl;
  cout << "4. Find and display faculty information given the faculty id" << endl;
  cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
  cout << "6. Given a faculty id, print ALL the names and info of his/her advisees" << endl;
  cout << "7. Add a new student" << endl;
  cout << "8. Delete a student given the id" << endl;
  cout << "9. Add a new faculty member" << endl;
  cout << "10. Delete a faculty member given the id" << endl;
  cout << "11. Change a student’s advisor given the student id and the new faculty id" << endl;
  cout << "12. Remove an advisee from a faculty member given the ids" << endl;
  cout << "13. Rollback" << endl;
  cout << "14. Exit" << endl;
  cout << GREEN << "15." << " Change student major" << RESET << endl;
}

void Menu::changeStudentMajor(int stuID, string newMajor, bool rb){
  rollback->insertFront("cngMajor " + to_string(stuID) + " " + studentTree->getData()->getMajor());
  studentTree->getData()->changeMajor(newMajor);
  if(rb){
    cout << "\nStudent " << GREEN << "ID#" << stuID << RESET << " is extremely indecisive and changed back to their previous major, " << newMajor <<  endl;
    return;
  }
  cout << "\nStudent " << GREEN << "ID#" << stuID << RESET << " was failing half their classes and changed majors to " << newMajor <<  endl;
}

void Menu::deleteStudent(int i_idNum, bool rollbackBool){
  int ph_advisor;
  if(studentTree->contains(i_idNum)){

    ph_advisor=studentTree->getData()->getAdvisor();

    string rb = studentTree->getData()->rollbackFormat();

    if(studentTree->deleteNode(i_idNum)){
      cout << "\nSuccessfully deleted student " << GREEN << "ID#" << i_idNum << RESET << " from database" << endl;

      if(!(ph_advisor==-1)){
        facultyTree->getData(ph_advisor)->removeAdvisee(i_idNum);
      }
      if(rollbackBool){
        rollback->insertFront("addStu " + rb);
      }
    }else{
      cout << "Error while deleting student from database" << endl;
    }
  }else{
    cout << "Student with ID#" << i_idNum << " does not exist." << endl;
  }
}

void Menu::deleteFaculty(int i_idNum, bool rollbackBool){
  if(facultyTree->contains(i_idNum)){
    string rb = facultyTree->getData()->rollbackFormat();
    int remID;
    if(facultyTree->getData()->adviseeCount()>0){
      for(int i = 0;i < facultyTree->getData()->adviseeCount(); ++i){
        studentTree->getData(facultyTree->getData()->getAdvisee(i))->removeAdvisor();
        cout << "Removed faculty advisor from student " << GREEN << "ID#" << facultyTree->getData()->getAdvisee(i) << RESET << endl;
      }
    }


    if(facultyTree->deleteNode(i_idNum)){
      cout << "\nSuccessfully deleted Faculty " << GREEN << "ID#" << i_idNum << RESET << " from database" << endl;
      if(rollbackBool){
        rollback->insertFront("addFac " + rb);
      }
    }else{
      cout << "Error while deleting faculty from database" << endl;
    }
  }else{
    cout << "Faculty with ID #" << i_idNum << " does not exist." << endl;
  }
}

void Menu::readFromFile(){ //Reads from files and performs necessary balancing to ensure advisor/advisee IDs exist

  ifstream inRB;
  inRB.open("masterRollback.txt");

  if(inRB.is_open()){
    cout << "Rollback file exists, restoring rollback history. Use with option 13." << endl;
    string ph_RB;
    while(!(inRB.eof())){
      getline(inRB,ph_RB);
      rollback->insertBack(ph_RB);
    }
  }

  DoublyLinkedList<int>* stuIDs = new DoublyLinkedList<int>();
  ifstream inFS;

    cout << "\nSearching and restoring student database from file masterStudent..." << endl;
    inFS.open("masterStudent.txt");

    if (!inFS.is_open()){
      cout << "masterStudent does not exist, empty student database created."<< endl;
    }else{

      string dummyLine;
      int idNum;
      string name;
      string level;
      string major;
      double gpa;
      int advisor;

      while (1){

        dummyLine = "";
        inFS >> idNum >> name >> level >> major >> gpa;
        getline(inFS,dummyLine);

        dummyLine.erase(0,1);
        if(inFS.eof()){
          break;
        }

        studentTree->insert(idNum, new Student(idNum,name,level,major,gpa));

        if(isdigit(dummyLine[0])){ //if an advisor is specified, add to student

          advisor = stoi(dummyLine);
          studentTree->getData(idNum)->setAdvisor(advisor);
          stuIDs->insertBack(idNum);
        }
      }
    }

  inFS.close();

  ifstream inFS_f;

  cout << "Searching and restoring student database from file masterFaculty..." << endl;
  inFS_f.open("masterFaculty.txt");

    if (!inFS_f.is_open()){
      cout << "masterFaculty does not exist, empty faculty database created."<< endl;
    }else{

      string dummyLine_f = "";
      string dummyID_f;
      int idNum_f;
      string name_f;
      string level_f;
      string department;

      while (1){
        try{
        dummyLine_f = "";
        dummyID_f = "";
        inFS_f >> idNum_f >> name_f >> level_f >> department;
        getline(inFS_f,dummyLine_f);

        dummyLine_f.erase(0,1);
        if(inFS_f.eof()){
          break;
        }

        facultyTree->insert(idNum_f, new Faculty(idNum_f,name_f,level_f,department));

        for(int i=0;i<dummyLine_f.size();++i){

          if(dummyLine_f[i]==' '){
            if(studentTree->contains(stoi(dummyID_f))){
              facultyTree->getData(idNum_f)->addAdvisee(stoi(dummyID_f));
              if(studentTree->getData()->hasAdvisor()){
                facultyTree->getData(studentTree->getData()->getAdvisor())->removeAdvisee(stoi(dummyID_f));
              }
              studentTree->getData()->setAdvisor(idNum_f);
            }else{
              cout << "Faculty " << GREEN << "ID#" << idNum_f << RESET << " was assigned an advisee that doesnt exist of " << GREEN << "ID#" << dummyID_f << RESET << endl;
            }
            dummyID_f = "";
          }else{
            dummyID_f = dummyID_f + dummyLine_f[i];
          }

        }
        if(studentTree->contains(stoi(dummyID_f))){
          facultyTree->getData(idNum_f)->addAdvisee(stoi(dummyID_f));
        }else{
          cout << "Faculty " << GREEN << "ID#" << idNum_f << RESET << " was assigned an advisee that doesnt exist of " << GREEN << "ID#" << dummyID_f << RESET << endl;
        }

        }catch(invalid_argument& e){

        }
      }
    }

  inFS_f.close();

  //check Linked lists is advisor/advisee IDs exist.
  int currID;
  while(stuIDs->getSize()>0){
    currID = stuIDs->removeFront();
    if(!(facultyTree->contains(studentTree->getData(currID)->getAdvisor()))){
      cout << "Student " << GREEN << "ID#" << studentTree->getData(currID)->idNum << RESET << " was assigned an advisor that doesnt exist of " << GREEN << "ID#" << studentTree->getData(currID)->getAdvisor() << RESET << endl;
      studentTree->getData(currID)->removeAdvisor();
    }else{
      if(!(facultyTree->getData()->containsAdvisee(currID))){
        facultyTree->getData()->addAdvisee(currID);
      }
    }

  }

  delete stuIDs;
  return;
}
