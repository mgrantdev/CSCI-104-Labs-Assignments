#include "avlbst.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split(string line) // Helper function to read the first line
{
    vector<string> res;
    stringstream ss(line);
    string buf;
    while (getline(ss, buf, ' '))
    {
        res.push_back(buf);
    }
    return res;
}

void printSolution(AVLTree<string, int> &classToTimeslot) // Print solution
{
    for (AVLTree<string, int>::iterator it = classToTimeslot.begin(); it != classToTimeslot.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
}

bool isValid(vector<vector<string>> classes, AVLTree<string, int> &classToTimeslot)
{
    for (int i = 0; i < classes.size(); i++) // A schedule is valid if for all students, their individual schedule is valid
    {
        AVLTree<int, int> set;
        int timeslot;
        vector<string> studentClasses = classes[i];
        for (int j = 0; j < studentClasses.size(); j++) // For a single student, its schedule is valid if all of its classes are scheduled to different timeslots
        {
            timeslot = classToTimeslot.find(studentClasses[j])->second;
            if (timeslot == -1) continue; // If this class is not scheduled, skip
            if (set.find(timeslot) != set.end()) return false; // We use a set to check if timeslots are all different to achieve O(log(n)) runtime
            set.insert(make_pair(timeslot, 0)); // 0 is just an arbitrary number since we are only using AVLTree as a set so value doesn't matter
        }
    }
    return true;
}

bool isEnd(AVLTree<string, int> &classToTimeslot)
{
    for (AVLTree<string, int>::iterator it = classToTimeslot.begin(); it != classToTimeslot.end(); ++it)
    {
        if (it->second == -1) return false; // We have scheduled all classes if none of them's timeslot is -1
    }
    return true;
}

void printAVLTree(AVLTree<string, int> &classToTimeslot) // Debug helper Python-style dictionary
{
    cout << "{";
    AVLTree<string, int>::iterator it = classToTimeslot.begin();
    cout << it->first << endl;
    
    for (AVLTree<string, int>::iterator it = classToTimeslot.begin(); it != classToTimeslot.end(); ++it)
    {
        cout << it->first << ": " << it->second << ", ";
    }
    cout << "}" << endl;
}

bool search(vector<vector<string>> classes, AVLTree<string, int> &classToTimeslot, vector<string> classesArr, int curClassIndex, int numTimeslots)
{
    if (isEnd(classToTimeslot)) // If we have sheduled every class
    {
        if (isValid(classes, classToTimeslot)) // If the current schedule is valid
        {
            printSolution(classToTimeslot);
            return true;
        }
        return false; // This schedule is wrong, backtrack
    }
    string curClass = classesArr[curClassIndex];
    if (classToTimeslot.find(curClass)->second == -1) // If this class has not been scheduled yet
    {
        for (int i = 1; i <= numTimeslots; i++) // Try all possible timeslots for this class
        {
            classToTimeslot.insert(make_pair(curClass, i));
            if (isValid(classes, classToTimeslot)) // If no conflicts yet
            {
                if (search(classes, classToTimeslot, classesArr, curClassIndex+1, numTimeslots)) return true; // Try to schedule the next class
            }
        }
        classToTimeslot.insert(make_pair(curClass, -1)); // Backtrack by marking this class as unscheduled
    }
    return false; // No solution
}

int main(int argc, char* argv[])
{
    if (argc < 2) // Check if there exists a file
    {
        cout << "Please provide a file name." << endl;
        return 0;
    }
    string fileName = argv[1];
    ifstream fin(fileName);
    string line;
    getline(fin, line);
    vector<string> firstLine = split(line); // Handle first line specially
    if (firstLine.size() < 3) // Check input format correctness
    {
        cout << "Input format is incorrect!" << endl;
        return 0;
    }
    int numClasses = stoi(firstLine[0]);
    int numStudents = stoi(firstLine[1]); // Actually we don't need this
    int numTimeslots = stoi(firstLine[2]);
    // Below are nothing but initialization of the data members I described in README
    vector<vector<string>> classes;
    AVLTree<string, int> classToTimeslot;
    vector<string> classesArr;
    while (getline(fin, line))
    {
        vector<string> vecLine;
        stringstream ss(line);
        string buf;
        ss >> buf;
        while (ss >> buf)
        {
            vecLine.push_back(buf);
        }
        vector<string> studentClasses;
        for (int i = 0; i < vecLine.size(); i++)
        {
            classToTimeslot.insert(make_pair(vecLine[i], -1)); // Initially set each class's timeslot to -1 (no schedule yet)
            studentClasses.push_back(vecLine[i]);
        }
        classes.push_back(studentClasses);
    }
    for (AVLTree<string, int>::iterator it = classToTimeslot.begin(); it != classToTimeslot.end(); ++it)
    {
        classesArr.push_back(it->first);
    }
    if (!search(classes, classToTimeslot, classesArr, 0, numTimeslots)) // Start the search and see if there's a solution
    {
        cout << "No valid solution." << endl;
    }
    return 0;
}