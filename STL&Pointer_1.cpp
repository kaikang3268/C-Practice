//HW3
//Name: Kai Kang
//Email: kkang04@syr.edu
//SUID: 913962441

#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
    string name;
    int section;
    int credits;
    course() {}
    course(string n, int s, int c) { name = n; section = s; credits = c; }
    bool operator == (course c) { return (name == c.name && section == c.section && credits == c.credits); }
    //Add additional needed member functions and implement them.
    //You also need to implement some needed functions for overloading operator<< .
};
//Implement the following functions

void add_student(map<int, map<int, list<course *> * > *> &DB, int id);
void remove_student(map<int, map<int, list<course *> * > *> &DB, int id);
void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017

void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course *> * > *> &DB, int id);
void print_DB(map<int, map<int, list<course *> * > *> &DB);

//For the print funcitons, you need to add more fucntions to overload operator<<.
//for example print_DB is simply cout << DB;

int main() {
    //Do not change code for main function
    map<int, map<int, list <course *> *> *> DB;
    add_student(DB, 11111);
    course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);
    
    add_course(DB, 20171, 11111, C1);
    add_course(DB, 20171, 11111, C4);
    add_course(DB, 20171, 11111, C3);
    add_course(DB, 20171, 11111, C2);
    print_student_semester_courses(DB, 20171, 11111);
    
    drop_course(DB, 20171, 11111, C1);
    print_student_semester_courses(DB, 20171, 11111);
    
    add_course(DB, 20172, 11111, C2);
    add_course(DB, 20172, 11111, C4);
    add_course(DB, 20172, 11111, C3);
    add_course(DB, 20172, 11111, C1);
    print_student_all_courses(DB, 11111);
    
    add_student(DB, 11112);
    add_course(DB, 20171, 11112, C2);
    add_course(DB, 20171, 11112, C4);
    add_course(DB, 20171, 11112, C3);
    add_course(DB, 20171, 11112, C1);
    print_student_semester_courses(DB, 20171, 11112);
    
    add_course(DB, 20172, 11112, C2);
    add_course(DB, 20172, 11112, C4);
    add_course(DB, 20172, 11112, C3);
    add_course(DB, 20172, 11112, C1);
    print_student_semester_courses(DB, 20172, 11112);
    print_student_all_courses(DB, 11112);
    print_DB(DB);
    remove_student(DB, 11111);
    print_DB(DB);
    getchar();
    getchar();
    return 0;
}

void add_student(map<int, map<int, list<course *> * > *> &DB, int id) {
    if(DB.find(id) != DB.end()) return;   //If the student id has already existed
    map<int, list<course *> * > *p = new map<int, list<course *> *>;
    DB[id] = p;
}

void remove_student(map<int, map<int, list<course *> * > *> &DB, int id) {
    //Student is not existed
    if (DB.size() == 0 || DB.find(id) == DB.end()) return;
    //semester is not existed
    if ((*(DB[id])).size() == 0) {
        DB.erase(id);
        return;
    }
    if(DB[id] == nullptr){
        delete DB[id];
        DB.erase(id);
        return;
    }
    map<int, list<course *> *>::iterator it1 = (*(DB[id])).begin();
    while (it1 != (*(DB[id])).end()) {
        if (it1->second->size() != 0) {
            list<course *>::iterator it2 = (*(it1->second)).begin();
            while(it2 != (*(it1->second)).end()) {
                delete *it2;
                //delete &it2;
                it2++;
            }
            it1->second->clear();
        }
        delete(it1->second);
        it1++;
    }
    DB.erase(id);
}


void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {
    //The student is not existed
    if(DB.find(id) == DB.end()) return;
    
    //Step 1: create a new semeter if DB pointing to nullptr
    if(DB[id] == nullptr){
        map<int, list<course *> *> *sem = new map<int, list<course *> *>;
        DB[id] = sem;
    }
    //Step 2: creat a new list
    //if the size of semester is 0 || there is no target semeter existed
    if((*(DB[id])).empty() || (*(DB[id])).find(semester) == (*(DB[id])).end()){
        list<course *> *li = new list<course *>;
        (*(DB[id])).insert({semester, li});
        (*li).push_back(new course(c));
    }
    //The student is existed && The semester is existed
    else {
        int flag = 0;
        auto it1 = (*(*(DB[id]))[semester]).begin();
        while(it1 != (*(*(DB[id]))[semester]).end()){
            if(*(*it1) == c)
                flag = 1;
            it1++;
        }
    if (flag == 1) return;    //If the course has already existed
    (*(DB[id]))[semester]->push_back(new course(c));
    }
}

void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {
    //Student is not existed or semester is not existed
    if (DB.find(id) == DB.end() || DB[id] == nullptr || (*(DB[id])).empty()
        || (*(DB[id])).find(semester) == (*(DB[id])).end()) return;
    //semester is existed
    auto it1 = (*(DB[id]))[semester]->begin();
    size_t i = 0;
    while (it1 != (*(DB[id]))[semester]->end()) {
        if(*(*it1) == c){
            delete *it1;
            (*(DB[id]))[semester]->erase(it1);
            break;
        }
        i++;
        it1++;
    }
}

void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id) {
    cout << endl;
    //If the student is not existed
    if (DB.size() == 0 || DB.find(id) == DB.end()) return;
    //If the student is existed but the semester is not existed, only print id
    if ((*(DB[id])).empty() || (*(DB[id])).find(semester) == (*(DB[id])).end()) return;
    cout << "student id = " << id << endl;
    //If the student is existed and the semester is existed
    if ((*(DB[id]))[semester]->size() != 0) {
        cout << "semester = " << semester << endl;
        auto it1 = (*(*(DB[id]))[semester]).begin();
        while(it1 != (*(*(DB[id]))[semester]).end()){
            cout << (*it1)->name << " " << (*it1)->section << " " << (*it1)->credits << "  ";
            it1++;
        }
        cout << endl;
    }
}

void print_student_all_courses(map<int, map<int, list<course *> * > *> &DB, int id) {
    cout << endl;
    //id is not existed
    if (DB.size() == 0 || DB.find(id) == DB.end()) return;
    //id is existed
    auto it1 = (*DB[id]).begin();
    cout << "student id = " << id << endl;
    while (it1 != (*DB[id]).end()) {
        cout << "semester = " << it1->first << endl;
        list<course *>::iterator it2 = it1->second->begin();
        while(it2 != it1->second->end()) {
            cout << (*it2)->name << " " << (*it2)->section << " " << (*it2)->credits << "  ";
            it2++;
        }
        cout << endl;
        it1++;
    }
}

void print_DB(map<int, map<int, list<course *> * > *> &DB) {
    cout << endl;
    if (DB.size() == 0) return;
    map<int, map<int, list<course *> *> *>::iterator it1 = DB.begin();
    while (it1 != DB.end()) {
        if (!(*(it1->second)).empty()) {
            cout << "student id = " << it1->first << endl;
            map<int, list<course *> *>::iterator it2 = (*(it1->second)).begin();
            while (it2 != (*(it1->second)).end()) {
                if (it2->second->size() != 0) {
                    cout << "semester = " << it2->first << endl;
                    auto it3 = (*(it2->second)).begin();
                    while(it3!=(*(it2->second)).end()){
                        cout << (*it3)->name << " " << (*it3)->section << " " << (*it3)->credits << "  ";
                        it3++;
                    }
                    cout << endl;
                }
                it2++;
            }
        }
        it1++;
    }
}
//Some additional functions for overloading operator<<


/*
 //Your output needs to keep the identical format
 //Sample Screenshot
 student id = 11111
 semester = 20171
 CIS554 1 3  WRT205 5 3  MAT296 8 4  CSE674 1 3
 
 student id = 11111
 semester = 20171
 WRT205 5 3  MAT296 8 4  CSE674 1 3
 
 student id = 11111
 semester = 20171
 WRT205 5 3  MAT296 8 4  CSE674 1 3
 semester = 20172
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 
 student id = 11112
 semester = 20171
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 
 student id = 11112
 semester = 20172
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 
 student id = 11112
 semester = 20171
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 semester = 20172
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 
 student id = 11111
 semester = 20171
 WRT205 5 3  MAT296 8 4  CSE674 1 3
 semester = 20172
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 student id = 11112
 semester = 20171
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 semester = 20172
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 
 student id = 11112
 semester = 20171
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 semester = 20172
 CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
 */
