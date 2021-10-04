#include "ArithmeticStatement.h"

ArithmeticStatement::ArithmeticStatement(std::string operation, std::string variableName, string strVal) {
    this->m_operation = operation;
    this->m_variableName = variableName;
    this->strValue = strVal;
}

void ArithmeticStatement::execute(ProgramState* state, std::ostream& outf) {
    state->arithmetic(this->m_operation, this->m_variableName, this->strValue);
}