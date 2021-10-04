#include "GotoStatement.h"

GotoStatement::GotoStatement(int line) { this->m_line = line; }

void GotoStatement::execute(ProgramState* state, ostream& outf) { state->goTo(this->m_line); }