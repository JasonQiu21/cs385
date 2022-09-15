/*******************************************************************************
 * Name        : student.cpp
 * Author      : Jason Qiu
 * Date        : September 15, 2022
 * Description : Student Class
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student{
public:
    Student(string first, string last, float gpa, int id);

    string full_name() const {return first_ + ' ' + last_;}
    int id() const {return id_;}
    float gpa() const {return gpa_;}
    void print_info() const;
private:
    string first_;
    string last_;
    float gpa_;
    int id_;
};

Student::Student(string first, string last, float gpa, int id): first_{first}, last_{last}, gpa_{gpa}, id_{id} {}

void Student::print_info() const{
    string gpa_str = to_string(gpa()).substr(0, 4);
    cout << full_name() << ", GPA: " << gpa_str << ", ID: " << id() << endl;
    
}

 
/** 
*  Takes a vector of Student objects, and returns a new vector 
*  with all Students whose GPA is < 1.0. 
*/ 
vector<Student> find_failing_students(const vector<Student> &students) { 
    vector<Student> failing_students; 
 
    // Iterates through the students vector, appending each student whose gpa is 
    // less than 1.0 to the failing_students vector. 
    for(Student i:students){
        if(i.gpa() < 1.0){
            failing_students.push_back(i);
        }
    }
    return failing_students; 
} 


/** 
*  Takes a vector of Student objects and prints them to the screen. 
*/ 
void print_students(const vector<Student> &students) { 
    for(Student i: students){
        i.print_info();
    }
} 


/** 
*  Allows the user to enter information for multiple students, then 
*  find those students whose GPA is below 1.0 and prints them to the 
*  screen. */ 
int main() { 
    string first_name, last_name; 
    float gpa; 
    int id; 
    char repeat; 
    vector<Student> students; 
 
    do { 
        cout << "Enter student's first name: "; 
        cin >> first_name; 
        cout << "Enter student's last name: "; 
        cin >> last_name; 
        gpa = -1; 
        while (gpa < 0 || gpa > 4) { 
            cout << "Enter student's GPA (0.0-4.0): "; 
            cin >> gpa; 
        } 
        cout << "Enter student's ID: "; 
        cin >> id; 
        students.push_back(Student(first_name, last_name, gpa, id)); 
        cout << "Add another student to database (Y/N)? "; 
        cin >> repeat; 
    } while (repeat == 'Y' || repeat == 'y'); 
 
    cout << endl << "All students:" << endl; 
    print_students(students); 
 
    cout << endl << "Failing students:"; 

    vector<Student> failing_students = find_failing_students(students);

    if(failing_students.size() > 0){
        cout << endl;
        for(Student i: failing_students){
            i.print_info();
        }
    } else {cout << " None" << endl;}
 
    return 0; 
} 