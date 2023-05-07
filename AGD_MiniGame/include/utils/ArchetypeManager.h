#pragma once
#include <vector>
#include <memory>
#include <unordered_map>

class System;

enum class ArchetypeID
{
    StaticEntity,
    DwarfPlayer,
    Fireball,
};
enum class SystemType { Logic, Graphics, Unknown };

class ArchetypeManager
{
public:
    ArchetypeManager();
	~ArchetypeManager();

    void addArchetypeSystems(ArchetypeID id, std::vector<std::shared_ptr<System>> _logicSystems, std::shared_ptr<System> _graphicsSystem);
    void addDebug(ArchetypeID id, std::shared_ptr<System> _system);
    std::vector<std::shared_ptr<System>> getSystems(ArchetypeID _id, std::string _systemType);

private:
    std::unordered_map<ArchetypeID, std::pair<std::vector<std::shared_ptr<System>>, std::vector<std::shared_ptr<System>>>> archetypeSystemMap;
    std::unordered_map<std::string, SystemType> enumTypeMap = {
        {"logic", SystemType::Logic},
        {"graphics", SystemType::Graphics}
    };
};