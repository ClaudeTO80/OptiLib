#pragma once
#include <functional>
#include <any>

class Bound
{
public:
    Bound(std::function<bool(std::any)> fn);
    bool isFeasible(std::any value);
private:
    std::function<bool(std::any)> m_fn;
};

class FreeBound : public Bound
{
public:
    FreeBound();
private:

};

class LowerBound : public Bound
{
public:
    LowerBound(std::any lb);
private:
    std::any m_lb{ 0 };
};

class UpperBound : public Bound
{
public:
    UpperBound(std::any ub);
private:
    std::any m_ub{ 0 };
};

class DoubleBound : public Bound
{
public:
    DoubleBound(std::any lb, std::any ub);
private:
    std::any m_lb{ 0 };
    std::any m_ub{ 0 };
};
//
//class ValuesBound : public Bound
//{
//public:
//    ValuesBound(std::set<std::any> values) :Bound([&](std::any value)
//        {
//            return  m_values.contains(value);
//        })
//    {
//        m_values = values;
//    }
//
//    /*bool isFeasible(std::any value) override 
//    { 
//        return m_values.contains(value);
//    }*/
//private:
//    std::set<std::any> m_values{};
//};

class ObjectiveDir
{

};

class ObjDirectionMinimize : public ObjectiveDir
{

};

class ObjDirectionMaximize : public ObjectiveDir
{

};

class ObjDirectionTarget : public ObjectiveDir
{

};

class ObjDirectionRange : public ObjectiveDir
{

};