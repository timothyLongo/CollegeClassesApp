// TIMOTHY LONGO
// THE SORTING PROJECT
// CS-300
// 7-1
// 10 / 13 / 2023


#include <iostream> // recognize input/ output stream
#include <fstream> // reads from files
#include <string> // to recognize strings
#include <vector> // to recognize vectors
#include <iomanip> // text formatting
#include <Windows.h> // for Sleep()
#include <sstream> // for reading files special cases
#include <algorithm> // for alphanumeric sorting


using namespace std;

// declaring vectors globally for simplicity
vector<string> courseVec;
vector<string> courseVecSorted; // we make copy to maintain the index of oringinal vec above
vector<string> prereqVec;


void notFoundScreen() {
	system("CLS");
	cout << setw(30) << setfill('\\') << "" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(10) << "" << "\x1B[31mNOT FOUND\033[0m" << setw(9) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << setw(30) << setfill('\\') << "" << endl;
	Sleep(2000);
}

void InvalidInputScreen() {
	system("CLS");
	cout << setw(30) << setfill('\\') << "" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(8) << "" << "\x1B[31mINVALID INPUT\033[0m" << setw(7) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << setw(30) << setfill('\\') << "" << endl;
	Sleep(2000);
}

// let's read a file
void readIt() {
	// we will use to vectors to accomplish this simple task
	// 1 - a string vector which cuts on the second comma
	// 2 - a string vector which only stores prereqs

	courseVec.clear();
	courseVecSorted.clear();
	prereqVec.clear();
	// we clear these for multipule operations
	// in case the user wants to see this more than once

	ifstream reader; // declares reading variable of ifstream
	reader.open("C:\\Users\\Timmy\\Documents\\THE_COURSE_FILE_TO_LOAD.txt");

	if (reader.is_open()) {
		while (!reader.eof() && !reader.fail()) { // while reader is not at the end of the line
			// and expected correct int or string type to read

			reader.clear();
			string tempCourseName;
			string temp; // rest of line after course name
			string loadIt;
			string prereq; // our prereqs
			getline(reader, tempCourseName, ',');
			getline(reader, temp);

			if (temp.find(',') == std::string::npos) {
				loadIt = tempCourseName + " " + temp;
				courseVec.push_back(loadIt);
				// here there are no prereqs so we do this
				prereqVec.push_back("none");
			}
			else {
				stringstream ss(temp);
				string tempStringStream;
				getline(ss, tempStringStream, ',');
				loadIt = tempCourseName + " " + tempStringStream;
				courseVec.push_back(loadIt);
				// here we find our prereqs
				getline(ss, prereq);
				prereqVec.push_back(prereq);
			}
		}
	}
	reader.close(); // reading finished

	// we need to maintain the index of the order
	// it was originally added because
	// each course.at(i) corresponds to prereq.at(i)

	// so we simply copy it over to sort in
	// a separate vector
	// simple

	// so let's make a copy
	// now that we populated the courseVec vector

	for (int i = 0; i < courseVec.size(); ++i) {
		courseVecSorted.push_back(courseVec.at(i));
	} // now we have our copy vector to sort


	system("CLS");
	cout << setfill('*') << setw(30) << "" << endl;
	cout << '*' << setfill(' ') << setw(28) << "" << '*' << endl;
	cout << '*' << setfill(' ') << setw(28) << "" << '*' << endl;
	cout << '*' << setfill(' ') << setw(7) << "" << "FILE LOADED =D" << setw(7) << "" << '*' << endl;
	cout << '*' << setfill(' ') << setw(28) << "" << '*' << endl;
	cout << '*' << setfill(' ') << setw(28) << "" << '*' << endl;
	cout << setfill('*') << setw(30) << "" << endl;
	Sleep(2000);
}

// let's sort a file
void sortIt() {
	system("CLS");
	// time to sort alpha numeric
	
	cout << endl; // visually appealing purposes
	cout << setfill('*') << setw(25) << "" << endl;
	cout << "*" << setfill(' ') << setw(23) << "" << "*" << endl;
	cout << "*" << setfill(' ') << setw(3) << "" << "COURSES SORTED =D" << setw(3) << "" << "*" << endl;
	cout << "*" << setfill(' ') << setw(23) << "" << "*" << endl;
	cout << setfill('*') << setw(25) << "" << endl;
	cout << endl;
	sort(courseVecSorted.begin(), courseVecSorted.end());
	for (int i = 0; i < courseVecSorted.size(); ++i) {
		cout << courseVecSorted.at(i) << endl;
	}
	// it's just that simple, using sort() :)
	string userIn;
	cout << endl;
	cout << "  enter any key to continue . . .  ";
	cin >> userIn;
}

// let's find your course
void findIt() {

	system("CLS");
	cout << endl; // visually appealing purposes
	cout << setfill('*') << setw(25) << "" << endl;
	cout << "*" << setfill(' ') << setw(23) << "" << "*" << endl;
	cout << "*" << setfill(' ') << setw(6) << "" << "MORE DETAILS" << setw(5) << "" << "*" << endl;
	cout << "*" << setfill(' ') << setw(23) << "" << "*" << endl;
	cout << setfill('*') << setw(25) << "" << endl;

	string userIn;
	cout << "   enter course ID (ex. MATH201). . .  ";
	cin >> userIn;

	// we will change the first 4 to uppercase
	// to work around case sensitivity

	std::transform(userIn.begin(), userIn.end(), userIn.begin(), ::toupper);

	if (cin.fail() || (userIn.length() != 7)) {
		cin.clear();
		cin.ignore(1000, '\n');
		InvalidInputScreen();
		findIt();
	}
	// now if it's not found

	// if it is found
	bool gotIt = false;
	for (int i = 0; i < courseVec.size(); ++i) {
		size_t found = courseVec.at(i).find(userIn);
		if (found != std::string::npos) {
			gotIt = true;

			system("CLS");
			cout << setfill('*') << setw(48) << "" << endl;
			cout << '*' << setfill(' ') << setw(46) << "" << '*' << endl;
			cout << "*  " << setw(44) << left << courseVec.at(i) << '*' << endl;
			cout << "*  Prerequisites:  " << setw(28) << left << prereqVec.at(i) << '*' << endl;
			cout << '*' << setfill(' ') << setw(46) << "" << '*' << endl;
			cout << setfill('*') << setw(48) << "" << endl;
			cout << endl;

			string userIn;
			cout << endl;
			cout << "  enter any key to continue . . .  ";
			cin >> userIn;
		}
	}
	if (gotIt == false) {
		notFoundScreen();
	}
}

void menu() {

	system("CLS");
	cout << setfill('*') << setw(30) << "" << endl;
	cout << '*' << setfill(' ') << setw(28) << "" << '*' << endl;
	cout << '*' << setfill(' ') << setw(9) << "" << "WELCOME TO" << setw(9) << "" << '*' << endl;
	cout << '*' << setfill(' ') << setw(28) << "" << '*' << endl;
	cout << '*' << setw(5) << "" << "THE SORTING PROJECT" << setw(4) << "" << '*' << endl;
	cout << '*' << setfill(' ') << setw(28) << "" << '*' << endl;
	cout << '*' << setw(4) << "" << "[ 1 ]  Load my file" << setw(5) << "" << '*' << endl;
	cout << '*' << setw(4) << "" << "[ 2 ]  Sort my courses" << setw(2) << "" << '*' << endl;
	cout << '*' << setw(4) << "" << "[ 3 ]  More details" << setw(5) << "" << '*' << endl;
	cout << '*' << setw(4) << "" << "[ 4 ]  Quit" << setw(13) << "" << '*' << endl;
	cout << '*' << setfill(' ') << setw(28) << "" << '*' << endl;
	cout << setfill('*') << setw(30) << "" << endl;
	cout << "  ENTER SELECTION:  ";

	int userIn;
	cin >> userIn;
	// simple input validation
	if (cin.fail() || (userIn < 1) || (userIn > 4)) {
		cin.clear();
		cin.ignore(1000, '\n');
		InvalidInputScreen();
		menu();
	}
	if (userIn == 1) {
		readIt();
	}
	if (userIn == 2) {
		sortIt();
	}
	if (userIn == 3) {
		findIt();
	}
	if (userIn == 4) {
		exit(0);
	}
}

int main() {

	while (true) {
		menu();
	}

	return 0;
}