#include "company.cpp"
#include <iostream>

using namespace std;

int main()
{
    // test from cs104 website
    cout << "test from cs104 website" << endl;
    CompanyTracker* test = new CompanyTracker(5);
    cout << "Initially" << endl;
    test->check();
    test->merge(0, 1);
    cout << "After merging 0 and 1" << endl;
    test->check();
    test->merge(2, 3);
    cout << "After merging 2 and 3" << endl;
    test->check();
    test->merge(0, 3);
    cout << "After merging 0 and 3" << endl;
    test->check();
    test->split(2);
    cout << "After splitting 2" << endl;
    test->check();
    test->split(2);
    cout << "After spliting 2" << endl;
    test->check();
    test->merge(2, 4);
    cout << "After merging 2 and 4" << endl;
    test->check();
    test->split(0);
    cout << "After splitting 0" << endl;
    test->check();

    // reset test
    // this delete is to avoid valgrind errors
    delete test;
    test = new CompanyTracker(5);

    // test for split edge cases
    cout << "" << endl;
    cout << "test for split edge cases, should output nothing with no errors" << endl;
    test->split(3);
    // test->check();
    test->split(-1);
    // test->check();
    test->split(100);
    test->check();

    // test for merge edge cases
    cout << "" << endl;
    cout << "test for merge edge cases, should ouput nothing with no errors" << endl;
    test->merge(1, 1);
    // test->check();
    test->merge(-1, 1);
    // test->check();
    test->merge(1, 6);
    test->merge(-5, 19);
    test->check();

    // test for inSameCompany edge cases
    cout << "" << endl;
    cout << "test for inSameCompany edge cases, should output true if i==j and false if i or j is out of range" << endl;
    cout << test->inSameCompany(1, 1) << endl;
    cout << test->inSameCompany(-1, 2) << endl;
    cout << test->inSameCompany(0, 5) << endl;

    delete test;
    return 0;
}