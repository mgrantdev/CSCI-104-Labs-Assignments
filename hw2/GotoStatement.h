#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "Statement.h"

class GotoStatement : public Statement {
private:
    int m_line;

public:
    GotoStatement(int line);

    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif