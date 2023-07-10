#include "Bounds.h"

Bound::Bound(std::function<bool(std::any)> fn) :m_fn(fn) {}
bool Bound::isFeasible(std::any value)
{
	return m_fn(value);
}

FreeBound::FreeBound() :Bound([](std::any) {return true; }) {}

LowerBound::LowerBound(std::any lb) :Bound([&](std::any value) {return std::any_cast<double>(m_lb) <= std::any_cast<double>(value); })
{
	m_lb = lb;
}

UpperBound::UpperBound(std::any ub) :Bound([&](std::any value) {return std::any_cast<double>(m_ub) >= std::any_cast<double>(value); })
{
	m_ub = ub;
}

DoubleBound::DoubleBound(std::any lb, std::any ub) :Bound([&](std::any value)
	{
		return      std::any_cast<double>(m_lb) <= std::any_cast<double>(value)
			&& std::any_cast<double>(m_ub) >= std::any_cast<double>(value);
	})
{
	m_lb = lb;
	m_ub = ub;
}

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