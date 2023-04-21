//
// Created by cakeal on 2023/4/20.
//
#include <iostream>
#include <vector>
//#include <algorithm>
using namespace std;

class Student{
private:
    int stuNum; //学号
    string stuName; //姓名
    //Major major; //该学生主修的专业 ID:-1为未确定专业
public:
    Student(int stuNum, string stuName);
    void ShowStuInfo();
    int GetStuNum();
};

Student::Student(int stuNum, string stuName) {
    this->stuName = stuName;
    this->stuNum = stuNum;
    //this->major = Major(-1, ""); //设置空专业
}

void Student::ShowStuInfo() {
    cout << stuNum << "-" << stuName << " ";
}

int Student::GetStuNum() {
    return stuNum;
}


class Major{
private:
    int ID;
    string majorName; //专业名
    vector<Student> students; //修该专业的学生们
public:
    Major(int ID, string majorName);
    void ShowMajorInfo();
    void AddStudent(Student student);
    void DelStudent(Student student);
};

Major::Major(int ID, string majorName) {
    this->ID = ID;
    this->majorName = majorName;
}

void Major::ShowMajorInfo() {
    cout << "Major " << ID << "-" << majorName << ": ";
    for(auto & student : students){
        student.ShowStuInfo();
    }
    cout << endl;
}

void Major::AddStudent(Student student) {
    this->students.push_back(student);
}

void Major::DelStudent(Student student) {
    for(/*vector<Student>::iterator*/auto i = students.begin(); i < students.end(); i++){
        if((*i).GetStuNum() == student.GetStuNum()){
            students.erase(i);
            return;
        }
    }
}

vector<Student> students;
vector<Major> majors;

int main(){
    char cmd;
    int stuNum = 0;
    int ID = 0;
    string stuName;
    string majorName;
    while(true){
        cin >> cmd;
        switch (cmd) {
            case 's':
                cin >> stuName;
                students.emplace_back(stuNum++, stuName);
                break;
            case 'n':
                for(auto & student : students){
                    student.ShowStuInfo();
                }
                cout << endl;
                break;
            case 'm':
                cin >> majorName;
                majors.emplace_back(ID++, majorName);
                break;
            case 'l':
                for(auto & major : majors){
                    major.ShowMajorInfo();
                }
                break;
            case 'a':
                cin >> stuNum >> ID;
                majors[ID].AddStudent(students[stuNum]);
                break;
            case 'd':
                cin >> stuNum >> ID;
                majors[ID].DelStudent(students[stuNum]);
                break;
            case 'v':
                int fromID, toID;
                cin >> fromID >> stuNum >> toID;
                majors[fromID].DelStudent(students[stuNum]);
                majors[toID].AddStudent(students[stuNum]);
                break;
            default:
                return 0;
        }
    }
    return 0;
}