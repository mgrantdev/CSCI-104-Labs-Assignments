#include <iostream>
#include "Person.h"

using namespace std;

int main() {
	// UscStudent* u = new UscStudent("Tommy Trojan", "Computer Science", 100);
	// u->setGPA(20);
	// u->printTranscript();
	Person* p = new UscStudent("Tommy Trojan", "cs", 100);
	p->printTitle();
	delete p;
	return 0;
}
