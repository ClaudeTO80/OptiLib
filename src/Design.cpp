#include "Design.h"

Design::Design(){}

Design::Design(std::shared_ptr<VariableSet> parameters, std::shared_ptr<ConstraintSet> constraints) :
    Design()
    
{
    //m_parameters = parameters;
    m_constraints = constraints;
}

bool Design::isFeasible()
{
    return m_parameters->isFeasibile();
}
