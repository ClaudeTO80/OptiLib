#pragma once
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

class UUIDHandler
{
public:

    static void generateRandom(std::string& id);
    static void generateRandom(Poco::UUID& id);

private:
    static Poco::UUIDGenerator m_uuidGenerator;
};
