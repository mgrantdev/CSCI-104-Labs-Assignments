#include "Person.h"
#include <iostream>

using namespace std;

Person::Person(std::string name) {
	mName = name;
}

void Person::printTitle()
{
	cout << "Person";
}

std::string Person::getName() {
	return mName;
}

Professor::Professor(std::string name, std::string department) : Person(name) {
	mName = name;
}

void Professor::printTitle()
{
	cout << "Professor";
}

std::string Professor::getDepartment() {
	return mDepartment;
}

Student::Student(std::string name, std::string major) : Person(name) {
	mName = name;
}

void Student::printTitle()
{
	cout << "Student";
}

void Student::setGPA(double gpa) {
	mGpa = gpa;
}

std::string Student::getMajor() {
	return mMajor;
}

UscStudent::UscStudent(std::string name, std::string major, double gpa) : Student(name, major) {
	mName = name;
	mMajor = major;
	setGPA(gpa);
}

void UscStudent::printTitle()
{
	cout << "USC Student";
}

void UscStudent::printTranscript() {
	cout << mName << " " << mGpa << " " << mMajor;
	// TO DO: fill in
}