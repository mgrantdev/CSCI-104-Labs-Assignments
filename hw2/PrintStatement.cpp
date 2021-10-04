// PrintStatement.cpp:
#include "PrintStatement.h"

PrintStatement::PrintStatement(std::string variableName) : m_variableName(variableName) {}

void PrintStatement::execute(ProgramState* state, std::ostream& outf) {
    if (this->m_variableName == "")
        state->printAll(outf);
    else
        state->print(this->m_variableName, outf);
}