#include "UUIDHandler.h"

Poco::UUIDGenerator UUIDHandler::m_uuidGenerator; // { Poco::UUIDGenerator::UUIDGenerator() };

void UUIDHandler::generateRandom(std::string& id)
{
    id = m_uuidGenerator.createRandom().toString();
}

void UUIDHandler::generateRandom(Poco::UUID& id)
{
    id = m_uuidGenerator.createRandom();
}

