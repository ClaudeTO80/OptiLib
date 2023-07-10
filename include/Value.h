#pragma once
#include <iostream>
#include <any>
#include "Bounds.h"

template<typename T>
concept isScalar = std::is_scalar_v<T>;

class Value
{
public:
    Value(std::any value);
    void setValue(std::any value);

    template<typename T>
    T getValue()
    {
        return std::any_cast<T>(m_value);
    }

    std::any getValue();

    virtual ~Value() { std::cout << __func__ << std::endl; }
    virtual void print() = 0;
    virtual void setValueInternal(std::any value) = 0;
    virtual const std::type_info& getType() = 0;
    bool isFeasible() 
    {
        return m_bound->isFeasible(m_value);
    }

     void setBound(std::shared_ptr<Bound> bound)
     {
         if (bound.get())
             m_bound = bound;
         else
             m_bound=std::make_shared<FreeBound>();
     }

protected:
private:
    std::any m_value;
    std::shared_ptr<Bound> m_bound{ std::make_shared<FreeBound>() };
};

template<typename T>
class ScalarValue :public Value
{
public:
    using Value::Value;
    virtual ~ScalarValue() { std::cout << __func__ << std::endl; }
    void print() override { std::cout << "Scalar" << std::endl; }
    void setValueInternal(std::any value) override
    {
        try {
            m_value = std::any_cast<T>(value);
        }
        catch (std::bad_any_cast& e)
        {
            std::cout << e.what() << " " << std::endl;
        }
    }

    T getValue()
    {
        return m_value;
    }

    const std::type_info& getType()
    {
        return typeid(T);
    }
private:
    T m_value;
};

template<typename T>
class ArrayValue :public Value
{
public:
    using Value::Value;
    virtual ~ArrayValue() { std::cout << __func__ << std::endl; }
    void print() override { std::cout << "Array" << std::endl; }
    void setValueInternal(std::any value) override
    {
        try {
            m_value = std::any_cast<T>(value);
        }
        catch (std::bad_any_cast& e)
        {
            std::cout << e.what() << " " << std::endl;
        }
    }

    const std::type_info& getType()
    {
        return typeid(std::decay<decltype(*m_value.begin())>::type);
    }

    T getValue()
    {
        return m_value;
    }

private:
    T m_value;
    std::type_info* m_type;
};