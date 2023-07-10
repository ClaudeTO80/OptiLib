#pragma once
#include <memory>
#include "Value.h"

class ValueFactory
{
public:
    template<typename isScalar>
    static std::shared_ptr<ScalarValue<isScalar>> create(isScalar v)
    {
        std::shared_ptr<ScalarValue<isScalar>> output = std::make_shared<ScalarValue<isScalar>>(v);
        output->setValue(v);
        return output;
    }

    template<typename T>
        requires (!isScalar<T>)
    static std::shared_ptr<ArrayValue<T>> create(T v)
    {
        std::shared_ptr<ArrayValue<T>> output = std::make_shared<ArrayValue<T>>(v);
        output->setValue(v);
        return output;
    }
};
