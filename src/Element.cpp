#include "Element.h"

const std::string& Element::getName() { return m_name; }
void Element::setValue(std::shared_ptr<Value> value)
{
	m_value = value;
	m_type = &(m_value->getType());
}

std::shared_ptr<Value> Element::getValue()
{
	return m_value;
}

void Element::setActive(bool value)
{
	m_active = value;
}

bool Element::isActive()
{
	return m_active;
}

bool Element::isFeasible()
{
	return m_value->isFeasible();
}

