#pragma once
#include "ElementSet.h"

class Design: public ObjId<Design>
{
public:
    Design();
    Design(std::shared_ptr<VariableSet> parameters, std::shared_ptr<ConstraintSet> constraints);

    template<typename T>
    std::shared_ptr<Design> addParameter(const std::string& name, T value)
    {
        m_parameters->add(name, value);
        return shared_from_this();
    }

    std::shared_ptr<Design> clone();
    bool isFeasible();

private:
    std::shared_ptr<ParameterSet> m_parameters;
    std::shared_ptr<VariableSet> m_variables;
    std::shared_ptr<ConstraintSet> m_constraints;
    //std::shared_ptr<ObjectiveSet> m_objs;

};
