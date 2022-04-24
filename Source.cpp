// Emily Wood
// CS 300
// Project 2
// 4/17/2022

# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <fstream>
# include <algorithm>

using namespace std;

// struct
struct Course {
	string number;
	string name;
	vector<string> prereqs;
};

// Menu Function
void DisplayMenu() {
	cout << endl << "1. Load Data Structure." << endl;
	cout << "2. Print Course List." << endl;
	cout << "3. Print Course." << endl;
	cout << "9. Exit." << endl << endl;
	cout << "What would you like to do? ";
}

// Function to split strings
vector<string> splitString(string fullString, string del = " ") {
	vector<string> result;
	int start = 0;
	int end = fullString.find(del);

	while (end != -1) {
		result.push_back(fullString.substr(start, end - start));
		start = end + del.size();
		end = fullString.find(del, start);
	}

	result.push_back(fullString.substr(start, end - start));

	return result;
}

// Load the file into a data structure
vector<Course> LoadFile(string file) {
	ifstream courseFile(file);

	vector<Course> courses;
	string line = "";

	if (courseFile.is_open()) {
		while (getline(courseFile, line)) {
			Course course;

			vector<string> data = splitString(line, ",");

			course.number = data[0];
			course.name = data[1];

			for (int i = 2; i < data.size(); ++i) {
				course.prereqs.push_back(data[i]);
			}
			courses.push_back(course);
		}
	}
	else {
		cout << "Cannot open file " << file << endl;
	}

	courseFile.close();

	return courses;

}

// Outputs the course
void CourseList(Course course) {

	cout << course.number << ", " << course.name << endl;

}

// Sorts the courses
void SortCourseList(vector<Course> &courses) {
	Course temp;

	for (int i = 0; i < courses.size() - 1; ++i) {
		for (int j = 0; j < courses.size() - 1; ++j) {
			if (courses[j].number > courses[j + 1].number) {
				temp = courses[j];
				courses[j] = courses[j + 1];
				courses[j + 1] = temp;

			}
		}

	}
}

// Searches for an inputed course, prints course information, including prerequisites
void PrintCourse(vector<Course> &courses, string courseChoice) {
	bool courseFound = false;

	for (int i = 0; i < courses.size(); ++i) {
		if (courses[i].number == courseChoice) {
			cout << endl << courses[i].number << ", " << courses[i].name << endl;
			cout << "Prerequisites: " << endl;

			if (courses[i].prereqs.size() == 0) {
				cout << "none" << endl;
			}
			else {
				for (int j = 0; j < courses[i].prereqs.size(); ++j) {
					cout << courses[i].prereqs[j] << endl;

				}
			}

			courseFound = true;
			break;
		}
	}
	
	if (!courseFound) {
		cout << endl << "Course not found." << endl;
	}
}

// verifies the user inputs a correct choice
bool GoodInput(char choice) {
	if (choice != '1' && choice != '2' && choice != '3' && choice != '9') {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	string file = "";
	char choice = '0';
	string courseChoice = "";
	char c;

	vector<Course> courses;

	cout << "Welcome to the course planner." << endl << endl;
	cout << "Which file would you like to load? ";
	cin >> file;

	// default file name for testing
	file = "CourseList.txt";

	while (choice != '9') {
		DisplayMenu();
		cin >> choice;
		if (GoodInput(choice)) {
			cout << endl << choice << " is not a valid option." << endl << endl;
			continue;
		}

		switch (choice) {
		case '1':
			courses = LoadFile(file);

			SortCourseList(courses);
			
			break;
		case '2':

			cout << endl << "Here is a sample schedule:" << endl << endl;
			for (int i = 0; i < courses.size(); ++i) {
				CourseList(courses[i]);
			}

			break;
		case '3':
			cout << endl << "What course would you like to know about? ";
			cin >> courseChoice;
			transform(courseChoice.begin(), courseChoice.end(), courseChoice.begin(), ::toupper);

			PrintCourse(courses, courseChoice);
			
			break;
		}
	}

	cout << endl << "Thank you for using the course planner!" << endl;
	return 0;
}
