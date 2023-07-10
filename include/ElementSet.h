#pragma once
#include <map>
#include <algorithm>
#include "Element.h"

template<typename T>
concept ElementTemplate = std::is_base_of_v<Element, T>;

template<typename ElementTemplate>
class ElementSet
{
public:

    template<typename T>
    void add(const std::string& name, T value)
    {
        if (!m_byName.contains(name))
            add(std::make_shared<ElementTemplate>(name, value));
    }

    std::shared_ptr<Value> getValue(const std::string& name)
    {
        return m_byName.contains(name) ? m_byName[name]->getValue() : nullptr;
    }

    bool isFeasibile()
    {
        return std::find_if_not(m_byName.begin(), m_byName.end(), [](std::pair<std::string, std::shared_ptr<Element>> curr) 
            {
                return curr.second->isFeasible();
            }) == m_byName.end();
    }

protected:
    void add(std::shared_ptr<ElementTemplate> element)
    {
        m_byName.emplace(element->getName(), element);
        m_byId.emplace(element->getId(), element);
    }

private:
    std::map<std::string, std::shared_ptr<Element>> m_byName;
    std::map<std::string, std::shared_ptr<Element>> m_byId;

};

class ParameterSet :public ElementSet<Parameter>
{


};

class VariableSet :public ElementSet<Variable>
{


};

class ConstraintSet :public ElementSet<Constraint>
{


};