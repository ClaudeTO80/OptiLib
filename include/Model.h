#pragma once
#include "Design.h"

class ModelFactory;

class Model: public Design
{
public:

private:
    friend class ModelFactory;
    Model(const std::string& name);
    Model(const std::string& name,std::shared_ptr<VariableSet> parameters, std::shared_ptr<ConstraintSet> constraints);
    std::string m_name{ "Model" };
};

class ModelFactory
{
public:
    static std::shared_ptr<Model> createModel(const std::string& name);
    static std::shared_ptr<Model> createModel(const std::string& name, std::shared_ptr<VariableSet> parameters, std::shared_ptr<ConstraintSet> constraints);

};
