#include "SubroutineStatement.h"

SubroutineStatement::SubroutineStatement(std::string control, int line) {
    this->m_control = control;
    this->m_line = line;
}

void SubroutineStatement::execute(ProgramState* state, std::ostream& outf) {
    state->subroutine(this->m_control, this->m_line);
}