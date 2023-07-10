#include "DesignSet.h"

DesignSet::DesignSet(std::shared_ptr<Design> defDesign) 
{
    m_defDesign = defDesign;
}

auto DesignSet::add(std::shared_ptr<Design> design)
{
    auto status = m_ids.emplace(design->getId(), design);

    if (status.second)
        m_designs.emplace_back(design);

    return status;
}

std::shared_ptr<Design> DesignSet::get(unsigned int i)
{
    try {
        return m_designs[i];
    }
    catch (std::exception& /*e*/)
    {
        return nullptr;
    }
}

std::shared_ptr<Design> DesignSet::getById(const std::string& id)
{
    try {
        return m_ids[id];
    }
    catch (std::exception& /*e*/)
    {
        return nullptr;
    }
}

//std::shared_ptr<Design> Design::create()
//{
//
//}