#include "company.hpp"
#include <iostream>
#include <vector>

using namespace std;

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n) {
    numCompanies = n;
    companies = new Company*[numCompanies];
    for (int i = 0; i < numCompanies; ++i)
        companies[i] = new Company();
}


// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker() {
    // your implementation goes here
    for (int i = 0; i < this->numCompanies; i++)
    {
        this->deleteAllParentsAndItself(this->companies[i]);
    }
    delete[] this->companies;
}

bool CompanyTracker::inFreed(Company* company)
{
    for (int i = 0; i < this->freed.size(); i++)
    {
        if (this->freed[i] == company) return true;
    }
    return false;
}

void CompanyTracker::merge(int i, int j) {
    // your implementation goes here
    // if the i or j is out of range
    if (i < 0 || i >= this->numCompanies || j < 0 || j >=this->numCompanies) return;
    // if merging the same company, we don't want to make the parent of that company itself
    if (i == j) return;
    Company* largestI = this->findLargest(i);
    Company* largestJ = this->findLargest(j);
    Company* merged = new Company(largestI, largestJ);
    largestI->parent = merged;
    largestJ->parent = merged;
}

void CompanyTracker::split(int i) {
    // your implementation goes here
    // if i is out of range
    if (i < 0 || i >= this->numCompanies) return;
    Company* largestI = this->findLargest(i);
    // if the company has only 1 student
    if (this->companies[i] == largestI) return;
    largestI->merge1->parent = nullptr;
    largestI->merge2->parent = nullptr;
    delete largestI;
}

bool CompanyTracker::inSameCompany(int i, int j) {
    // your implementation goes here
    if (i < 0 || i >= this->numCompanies || j < 0 || j >= this->numCompanies) return false;
    return this->findLargest(i) == this->findLargest(j);
}

Company* CompanyTracker::findLargest(int i) {
    Company* company = this->companies[i];
    while (company->parent != nullptr)
    {
        company = company->parent;
    }
    return company;
}

void CompanyTracker::deleteAllParentsAndItself(Company* company)
{
    if (!this->inFreed(company->parent) && company->parent != nullptr) this->deleteAllParentsAndItself(company->parent);
    this->freed.push_back(company);
    delete company;
}

void CompanyTracker::check()
{
    for (int i = 0; i < this->numCompanies - 1; i++)
    {
        for (int j = i + 1; j < this->numCompanies; j++)
        {
            if (this->inSameCompany(i, j))
            {
                cout << i << " and " << j << " are in the same company" << endl;
            }
            else
            {
                cout << i << " and " << j << " are not in the same company" << endl;
            }
        }
    }
}