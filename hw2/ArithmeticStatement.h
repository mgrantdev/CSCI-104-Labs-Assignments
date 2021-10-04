#ifndef ARITHMETIC_STATEMENT_INCLUDED
#define ARITHMETIC_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class ArithmeticStatement : public Statement {
private:
    std::string m_operation;
    std::string m_variableName;
    std::string strValue;

public:
    ArithmeticStatement(std::string opreation, std::string variableName, string strVal);

    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif