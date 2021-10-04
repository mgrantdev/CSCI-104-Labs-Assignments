#include <string>

class Person {
	public:
		Person(std::string name);
		std::string getName();
		virtual void printTitle();
	protected:
		std::string mName;
		int mAge;
};

class Professor : public Person {
	public:
		Professor(std::string name, std::string department);
		std::string getDepartment();
		void printTitle();
	private:
		int mSalary;
		std::string mDepartment;
};

class Student : protected Person {
	public:
		Student(std::string name, std::string major);
		std::string getMajor();
		void setGPA(double gpa);
		virtual void printTitle();
	protected:
		std::string mMajor;
	protected:
		double mGpa;
};

class UscStudent : public Student {
	public:
		UscStudent(std::string name, std::string major, double gpa);
		std::string getUscEmail();
		void printTranscript();
		void printTitle();
	private:
		int mUscID;
		std::string mUscEmail;
};