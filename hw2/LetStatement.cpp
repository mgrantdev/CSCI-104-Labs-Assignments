// LetStatement.cpp:
#include "LetStatement.h"

LetStatement::LetStatement(std::string variableName, int value) : m_variableName(variableName), m_value(value) {}

// LetStatement::LetStatement(std::string variableName, int value)
// {
// 	this->m_variableName = variableName;
// 	this->m_value = value;
// }

// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void LetStatement::execute(ProgramState* state, ostream& outf) {
    // TODO
    state->letVariable(this->m_variableName, this->m_value);
}
