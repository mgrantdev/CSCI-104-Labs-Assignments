// ProgramState.h
//
// CS 104 / Fall 2021
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include <iostream>
#include <map>
#include <math.h>
#include <stack>
#include <string>

using namespace std;

class ProgramState {
public:
    ProgramState(int numLines);

    // You'll need to add a variety of methods here.  Rather than trying to
    // think of what you'll need to add ahead of time, add them as you find
    // that you need them.

    int getCounter();

    bool isEnd();

    void letVariable(string variableName, int value);

    void print(string variableName, ostream& outf);

    void printAll(ostream& outf);

    void setEnd();

    void goTo(int line);

    void arithmetic(string operation, string variableName, string strValue);

    void evaluate(string variableName, string operation, int value, int line);

    void subroutine(string control, int line);

private:
    int m_numLines;
    int counter;
    bool end;
    map<string, int> variables;
    stack<int> returnLines;
};

#endif
