// ==========================================
// Title: Project2.cpp
// Author: Hannah Rath
// ==========================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

//Structure to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};


//Load Data Structure
void loadDataStructure(string filename, vector<Course>& courses) {
    ifstream file(filename);
    string line;

    //check if file opened correctly
    if (!file.is_open()) {
        cout << "Error: Could not open file" << endl;
        return;
    }

    //separate data into tokens
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string>tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Format Error" << line << endl;
            continue;
        }

        //create course objects
        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        if (tokens.size() > 2) {
            for (int i = 2; i < tokens.size(); ++i) {
                course.prerequisites.push_back(tokens[i]);
            }
        }
        courses.push_back(course);
    }
    file.close();
    cout << "Courses loaded successfully" << endl;

    //validate Prerequisites
    for (const auto& course : courses) {
        for (const auto& prereq : course.prerequisites) {
            bool found = false;
            for (const auto& c : courses) {
                if (c.courseNumber == prereq) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Error: Prerequisite " << prereq << " for " << course.courseNumber << " not found" << endl;
            }
        }
    }
}

//print all courses sorted alphanumerically
void printSortedList(vector<Course> courses) {
   //validata thet data is loaded
    if (courses.size() > 0) {
        //sort courses alphanumerically
        for (int i = 0; i < courses.size() - 1; ++i) {
            for (int j = 0; j < courses.size() - i - 1; ++j) {
                if (courses[j].courseNumber > courses[j + 1].courseNumber) {
                    swap(courses[j + 1], courses[j]);
                }
            }
       }
        //printed sorted course list
        cout << "Here is a sample schedule:" << endl;
        cout << endl;
        for (int i = 0; i < courses.size(); ++i) {
            cout << courses[i].courseNumber << ", " << courses[i].courseTitle << endl;
        }
        cout << endl;
    }
    //error message if data was not loaded first
    else {
        cout << "Error: No data loaded. Please use Option 1 first." << endl;
    }
}

//search and print course info
void printCourseInfo(const vector<Course>& courses) {
    //validate that data is loaded
    if (courses.size() > 0) {
        string target;
        bool foundCourse = false;

        //get user search item
        cout << "What course do you want to know about? ";
        cin >> target;

        //change input from lowercase to uppercase
        transform(target.begin(), target.end(), target.begin(), ::toupper);

        //seach for course
        for (int i = 0; i < courses.size(); ++i) {
            if (courses[i].courseNumber == target) {
                foundCourse = true;

                //Print course number and title
                cout << endl;
                cout << courses[i].courseNumber << ", " << courses[i].courseTitle << endl;
                cout << "Prerequisites: ";

                //search and print prerequisistes
                if (courses[i].prerequisites.size() > 0) {
                    int prereqSize = courses[i].prerequisites.size();

                    for (int j = 0; j < prereqSize - 1; ++i) {
                        cout << courses[i].prerequisites[j] << ", ";
                    }
                    cout << courses[i].prerequisites[prereqSize - 1];
                    cout << endl;
                }
                else {
                    cout << "None" << endl;
                }
            }
        }
        //error is course is not found
        if (foundCourse == false) {
            cout << "Invalid course, please try again" << endl;
        }
    }
    //error message if data was not loaded first
    else {
        cout << "Error: No data loaded. Please use Option 1 first." << endl;
    }
}
int main() {
    vector<Course> courses;
    string filename = "CS 300 ABCU_Advising_Program_Input.csv";
    int choice = 0;

    //greeting
    cout << "Welcome to the ABCU Advising Program" << endl;

    //menu
    while (choice != 9) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit." << endl;
        cout << "\n What would you like to do? ";

        //invalid input
        if (!(cin >> choice)) {
            cout << choice << " is not a valid option." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        //handle user choice
        switch (choice) {
        case 1:
            loadDataStructure(filename, courses);
            break;

        case 2:
            printSortedList(courses);
            break;

        case 3:
            printCourseInfo(courses);
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }
    return 0;
}
