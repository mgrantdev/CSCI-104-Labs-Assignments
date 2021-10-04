// Interpreter.cpp
#include "ArithmeticStatement.h"
#include "ConditionStatement.h"
#include "EndStatement.h"
#include "GotoStatement.h"
#include "LetStatement.h"
#include "PrintStatement.h"
#include "Statement.h"
#include "SubroutineStatement.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement*>& program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement* parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);

int main() {
    cout << "Enter BASIC program file name: ";
    string filename;
    getline(cin, filename);
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "Cannot open " << filename << "!" << endl;
        return 1;
    }
    interpretProgram(infile, cout);
}

void parseProgram(istream& inf, vector<Statement*>& program) {
    program.push_back(NULL);

    string line;
    while (!inf.eof()) {
        getline(inf, line);
        program.push_back(parseLine(line));
    }
    // cout << "hi" << endl;
}

Statement* parseLine(string line) {
    Statement* statement;
    stringstream ss;
    string type;
    string var;
    int lineNum;
    int val;
    int goTo;

    ss << line;
    ss >> lineNum;
    ss >> type;

    if (type == "LET") {
        ss >> var;
        ss >> val;
        // Note:  Because the project spec states that we can assume the file
        //	  contains a syntactically legal program, we know that
        //	  any line that begins with "LET" will be followed by a space
        //	  and then a variable and then an integer value.
        statement = new LetStatement(var, val);
    }

    if (type == "PRINT") {
        ss >> var;
        statement = new PrintStatement(var);
    }

    if (type == "PRINTALL") {
        statement = new PrintStatement("");
    }

    if (type == "." || type == "END") {
        statement = new EndStatement();
    }

    if (type == "GOTO") {
        ss >> goTo;
        statement = new GotoStatement(goTo);
    }

    if (type == "ADD" || type == "SUB" || type == "MULT" || type == "DIV") {
        string strVal;
        ss >> var;
        ss >> strVal;
        statement = new ArithmeticStatement(type, var, strVal);
    }

    if (type == "IF") {
        string then;
        string operation;
        int line_num;
        ss >> var;
        ss >> operation;
        ss >> val;
        ss >> then;
        ss >> line_num;
        statement = new ConditionStatement(var, operation, val, line_num);
    }

    if (type == "GOSUB") {
        int line_num;
        ss >> line_num;
        statement = new SubroutineStatement(type, line_num);
    }
    if (type == "RETURN") {
        statement = new SubroutineStatement(type, 0);
    }

    // Incomplete;  TODO:  Finish this function!

    return statement;
}

void interpretProgram(istream& inf, ostream& outf) {
    vector<Statement*> program;
    parseProgram(inf, program);

    // Incomplete;  TODO:  Finish this function!
    ProgramState* state = new ProgramState(program.size() - 1);
    while (!state->isEnd()) {
        program[state->getCounter()]->execute(state, outf);
    }
    // clear memory
    for (int i = 1; i < program.size(); i++) {
        delete program[i];
    }
    delete state;
}
