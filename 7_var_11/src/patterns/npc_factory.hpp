#pragma once
#include <memory>
#include <string>
#include "../npc/types.hpp"

class NPC;

class NPCFactory {
public:
    static std::shared_ptr<NPC> create(int id, NPCType t, const std::string& name, double x, double y);
    static std::shared_ptr<NPC> fromLine(const std::string& line);
};
