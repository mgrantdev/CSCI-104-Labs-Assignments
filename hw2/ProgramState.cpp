#include "ProgramState.h"

using namespace std;

ProgramState::ProgramState(int numLines) {
    this->m_numLines = numLines;
    // the program starts at line 1
    this->counter = 1;
    // the program is not end yet
    this->end = false;
}

int ProgramState::getCounter() {
    // so that in Interpreter.cpp we can get the counter to check for goto-ish statements
    return this->counter;
}

bool ProgramState::isEnd() {
    // so that in Interpreter we know where to stop
    return this->end;
}

// After every "normal(non-executation) statements" we increase the line number by 1
void ProgramState::letVariable(string variableName, int value) {
    this->variables[variableName] = value;
    this->counter += 1;
}

void ProgramState::print(string variableName, ostream& outf) {
    outf << this->variables[variableName] << endl;
    this->counter += 1;
}

void ProgramState::printAll(ostream& outf) {
    for (map<string, int>::iterator it = this->variables.begin(); it != this->variables.end(); ++it) {
        outf << it->first << " " << it->second << endl;
    }
    this->counter += 1;
}

// for EndStatement execute()
void ProgramState::setEnd() { this->end = true; }

void ProgramState::goTo(int line) {
    // check if the line number is out of bounds
    if (line <= 0 || line > this->m_numLines) {
        cout << "Illegal jump instruction" << endl;
        exit(0);
    }
    // directly set the current line to the line we are going to jump to
    else
        this->counter = line;
}

void ProgramState::arithmetic(string operation, string variableName, string strValue) {
    // if this variable is not found but referenced, set it to 0
    if (this->variables.find(variableName) == this->variables.end())
        this->variables[variableName] = 0;
    int value;
    // using ASCII to judge whether the third parameter is a variable name or a number, if number then stoi, if variable
    // then get that variable's value
    if (strValue[0] == '-' || (int(strValue[0]) >= 48 && int(strValue[0]) <= 57))
        value = stoi(strValue);
    else
        value = this->variables[strValue];
    if (operation == "ADD")
        this->variables[variableName] += value;
    else if (operation == "SUB")
        this->variables[variableName] -= value;
    else if (operation == "MULT")
        this->variables[variableName] *= value;
    else if (operation == "DIV") {
        // cannot divide by 0
        if (value == 0) {
            cout << "Divide by zero exception" << endl;
            exit(0);
        } else {
            // if the result is negative, rounding down means away from zero so - 1
            if (this->variables[variableName] < 0 && value > 0)
                this->variables[variableName] = floor(this->variables[variableName] / value - 1);
            else if (this->variables[variableName] > 0 && value < 0)
                this->variables[variableName] = floor(this->variables[variableName] / value - 1);
            else
                this->variables[variableName] /= value;
        }
    }
    this->counter += 1;
}

// for ConditionStatement execute()
void ProgramState::evaluate(string variableName, string operation, int value, int line) {
    // if this variable is not found but referenced, set it to 0
    if (this->variables.find(variableName) == this->variables.end())
        this->variables[variableName] = 0;
    bool execute = false;
    if (operation == "<")
        execute = this->variables[variableName] < value;
    else if (operation == "<=")
        execute = this->variables[variableName] <= value;
    else if (operation == ">")
        execute = this->variables[variableName] > value;
    else if (operation == ">=")
        execute = this->variables[variableName] >= value;
    else if (operation == "=")
        execute = this->variables[variableName] == value;
    else if (operation == "<>")
        execute = this->variables[variableName] != value;
    if (execute) {
        // check if the line we are going to jump to is out of bounds
        if (line <= 0 || line > this->m_numLines) {
            cout << "Illegal jump instruction" << endl;
            exit(0);
        } else
            this->goTo(line);
    }
    // if the statement is not satisfied, we directly go to the next line
    else
        this->counter += 1;
}

void ProgramState::subroutine(string control, int line) {
    if (control == "GOSUB") {
        // check out of bounds
        if (line <= 0 || line > this->m_numLines) {
            cout << "Illegal jump instruction" << endl;
            exit(0);
        } else {
            // push this->counter+1 because we are not going to jump again after return, otherwise it is an infinite
            // loop
            this->returnLines.push(this->counter + 1);
            this->goTo(line);
        }
    } else if (control == "RETURN") {
        // check if a return is before any gosub
        if (this->returnLines.empty())
            exit(0);
        else {
            int returnLine = this->returnLines.top();
            this->returnLines.pop();
            this->goTo(returnLine);
        }
    }
}