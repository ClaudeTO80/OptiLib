#include "Value.h"

Value::Value(std::any value)
{
	m_value = value;
}
void Value::setValue(std::any value) {
	m_value = value;
	setValueInternal(value);
}

std::any Value::getValue()
{
	return m_value;
}


