#ifndef CONDITION_STATEMENT_INCLUDED
#define CONDITION_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

class ConditionStatement : public Statement {
private:
    std::string m_variableName;
    std::string m_operation;
    int m_value;
    int m_line;

public:
    ConditionStatement(std::string variableName, std::string operation, int value, int line);

    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif