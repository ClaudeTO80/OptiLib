#pragma once
#include "UUIDHandler.h"

template<typename T>
class ObjId: public std::enable_shared_from_this<T>
{
public:

    /*ObjId();
    ObjId(const std::string& id);
    void setId();
    void setId(const std::string& id);
    const std::string& getId();*/

    ObjId()
    {
        setId();
    }

    ObjId(const std::string& id)
    {
        setId(id);
    }

    void setId()
    {
        UUIDHandler::generateRandom(m_id);
    }

    void setId(const std::string& id)
    {
        m_id = id;
    }
    const std::string& getId()
    {
        return m_id;
    }

private:
    std::string m_id{ "" };
};
