//
// Created by cakeal on 2023/4/20.
//
#include <iostream>
#include <vector>
using namespace std;

class Course{
private:
    string courseName; //课程名
    int prerequisites; //先修课
    int ID; // 课程ID
public:
    Course(const string& courseName, int prerequisites, int ID);
    void ShowCourseInfo();
    string FindPrerequisites(int pre) const;
};

vector<Course> courses;

Course::Course(const string& courseName, int prerequisites, int ID) {
    this->courseName = courseName;
    this->prerequisites = prerequisites;
    this->ID = ID;
}

void Course::ShowCourseInfo() {
    if(prerequisites == -1){
        cout << "Course " << ID << "-" << courseName << " has prerequisites: none" << endl;
        return;
    }
    cout << "Course " << ID << "-" << courseName << " has prerequisites: " << FindPrerequisites(prerequisites) << endl;
}

string Course::FindPrerequisites(int pre) const {
    if(prerequisites == -1) return "";
    return courses[pre].courseName + " " + courses[pre].FindPrerequisites(courses[pre].prerequisites);
}

int main(){
    char cmd;
    string courseName;
    int ID = 0;
    int prerequisites;
    while(true){
        cin >> cmd;
        switch (cmd) {
            case 'c':
                cin >> courseName >> prerequisites;
                //courses.push_back(Course(courseName, prerequisites, ++ID));
                courses.emplace_back(courseName, prerequisites, ID++);
                break;
            case 's':
                for (auto i : courses) {
                    i.ShowCourseInfo();
                }
                break;

            default:
                return 0;
        }
    }
    return 0;
}