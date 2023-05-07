#include "../../include/systems/Systems.h"
#include "../../include/utils/ArchetypeManager.h"

ArchetypeManager::ArchetypeManager()
{

}
ArchetypeManager::~ArchetypeManager()
{

}

void ArchetypeManager::addArchetypeSystems(ArchetypeID id, std::vector<std::shared_ptr<System>> _logicSystems, std::shared_ptr<System> _graphicsSystem)
{
	auto graphics = std::vector<std::shared_ptr<System>> { _graphicsSystem };
	archetypeSystemMap[id] = { _logicSystems, graphics };
}

void ArchetypeManager::addDebug(ArchetypeID id, std::shared_ptr<System> _system)
{
	archetypeSystemMap[id].second.push_back(_system);
}

std::vector<std::shared_ptr<System>> ArchetypeManager::getSystems(ArchetypeID _id, std::string _systemType)
{
    // check if string is in enum map - if yes return the corresponding enum, if not return unknown for exception raising
    SystemType systemType = enumTypeMap.count(_systemType) ? enumTypeMap[_systemType] : SystemType::Unknown;
    switch (systemType)
    {
    case SystemType::Logic:
        return archetypeSystemMap[_id].first; // first vector in vector pair are logic systems

    case SystemType::Graphics:
        return archetypeSystemMap[_id].second; // second vector in vector pair are graphic systems

    case SystemType::Unknown:
    default:
        std::cerr << "Unknown system type: " << _systemType << std::endl;
        std::vector<std::shared_ptr<System>> empty{};
        return empty;
    }
}
