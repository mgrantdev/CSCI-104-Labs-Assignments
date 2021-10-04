#ifndef SUBROUTINE_STATEMENT_INCLUDED
#define SUBROUTINE_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

class SubroutineStatement : public Statement {
private:
    std::string m_control;
    int m_line;

public:
    SubroutineStatement(std::string control, int line);

    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif