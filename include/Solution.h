#pragma once
#include <memory>
#include "ElementSet.h"

class Solution
{
public:

private:
    std::shared_ptr<VariableSet> m_varset{ new VariableSet() };
    std::shared_ptr<ConstraintSet> m_constrset{ new ConstraintSet() };
};