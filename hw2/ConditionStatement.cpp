#include "ConditionStatement.h"

ConditionStatement::ConditionStatement(std::string variableName, std::string operation, int value, int line) {
    this->m_variableName = variableName;
    this->m_operation = operation;
    this->m_value = value;
    this->m_line = line;
}

void ConditionStatement::execute(ProgramState* state, std::ostream& outf) {
    state->evaluate(this->m_variableName, this->m_operation, this->m_value, this->m_line);
}