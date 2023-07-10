#include "Model.h"

Model::Model(const std::string& name) :
	m_name(name) 
{}

Model::Model(const std::string& name, std::shared_ptr<VariableSet> parameters, std::shared_ptr<ConstraintSet> constraints):
	Design(parameters,constraints)
{
	m_name=name;
}

std::shared_ptr<Model> ModelFactory::createModel(const std::string& name)
{
	return std::shared_ptr<Model>(new Model(name));
}

std::shared_ptr<Model> ModelFactory::createModel(const std::string& name, std::shared_ptr<VariableSet> parameters, std::shared_ptr<ConstraintSet> constraints)
{
	return std::shared_ptr<Model>(new Model(name,parameters,constraints));
}

