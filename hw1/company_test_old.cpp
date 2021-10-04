#include "company.cpp"
#include <iostream>

using namespace std;

void printParents(CompanyTracker* test) {
    for (int i = 0; i < 5; i++) {
        cout << test->getCompany(i)->parent << endl;
    }
}

int main() {
    CompanyTracker* test = new CompanyTracker(5);
    // test->merge(0, 1);
    // printParents(test);
    // test->findLargest(2);
    // cout << "0x6a1790" << endl;
    cout << "The new merged company is:" << endl;
    test->merge(0, 1);
    cout << "After merge 0, 1:" << endl;
    printParents(test);
    cout << "The new merged company is:" << endl;
    test->merge(2, 3);
    cout << "After merge 2, 3:" << endl;
    printParents(test);
    cout << "The new merged company is:" << endl;
    test->merge(0, 3);
    cout << "After merge 0, 3:" << endl;
    printParents(test);
    cout << "---" << endl;
    cout << test->companies[0]->parent->parent << endl;
    cout << "---" << endl;
    test->split(2);
    cout << "After split 2:" << endl;
    printParents(test);
    cout << "---" << endl;
    cout << test->companies[0]->parent->parent << endl;
    cout << "---" << endl;
    cout << "After split 2 again:" << endl;
    test->split(2);
    printParents(test);
    cout << "---" << endl;
    test->split(2);
    printParents(test);
    // test->merge(1, 2);
    // printParents(test);
    // test->findLargest(0);
    // test->findLargest(1);
    // test->findLargest(1);
    delete test;
    return 0;
}