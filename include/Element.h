#pragma once
#include <string>
#include <memory>
#include <type_traits>
#include "ObjId.h"
#include "ValueFactory.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

class Element: public ObjId<Element>
{
public:
    template<typename T>
    Element(const std::string& name, T value) :
        ObjId(), 
        m_name(name)
    {
        setValue(ValueFactory::create(value));
    }

    template<typename T>
    Element(const std::string& name, T value, const std::string& id) :
        ObjId(id),
        m_name(name)
    {
        setValue(ValueFactory::create(value));
    }

    const std::string& getName();
    void setValue(std::shared_ptr<Value> value);
    std::shared_ptr<Value> getValue();
    void setActive(bool value);
    bool isActive();
    bool isFeasible();

private:
    std::shared_ptr<Value> m_value;
    const std::type_info* m_type;
    std::string m_name{ "" };
    bool m_active{ true };
    
};

class Parameter : public Element
{
public:
    using Element::Element;

};

class DesignElement /*: public Element*/
{
public:
    DesignElement(std::shared_ptr<Parameter> parameter) : m_parameter(parameter) {}
    DesignElement(std::shared_ptr<Parameter> parameter,bool active) : 
        DesignElement(parameter)
    {
        setActive(active);
    }

    void setActive(bool value) { m_isActive = value; }
    bool isActive() { return m_isActive; }
protected:
    std::shared_ptr<Parameter> m_parameter;
    bool m_isActive{ false };
};

class Variable : public DesignElement
{
public:
    using DesignElement::DesignElement;
private:
    std::shared_ptr<Bound> m_bound{ std::make_shared<FreeBound>() };
};

class Constraint : public DesignElement
{
public:
    using DesignElement::DesignElement;
private:
    std::shared_ptr<Bound> m_bound{ std::make_shared<FreeBound>() };
};

class Objective : public DesignElement
{
public:
    using DesignElement::DesignElement;
private:
    std::shared_ptr<ObjectiveDir> m_objDir{ std::make_shared<ObjDirectionMinimize>() };
};