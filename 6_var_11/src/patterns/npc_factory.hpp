#pragma once
#include <memory>
#include <string>
#include "../npc/types.hpp"

class NPC;

class NPCFactory {
public:
    static std::unique_ptr<NPC> create(NPCType t, const std::string& name, double x, double y);
    static std::unique_ptr<NPC> fromLine(const std::string& line);
};
