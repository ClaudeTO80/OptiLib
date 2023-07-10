#pragma once
#include <vector>
#include <map>
#include "Design.h"

class DesignSet
{
public:
    DesignSet(std::shared_ptr<Design> defDesign);
    std::shared_ptr<Design> create();
    auto add(std::shared_ptr<Design> design);
    std::shared_ptr<Design> get(unsigned int i);
    std::shared_ptr<Design> getById(const std::string& id);

private:
    std::vector<std::shared_ptr<Design>> m_designs;
    std::map<std::string,std::shared_ptr<Design>> m_ids;
    std::shared_ptr<Design> m_defDesign;

};
