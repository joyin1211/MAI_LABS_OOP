#pragma once
#include "npc.hpp"
#include <string>

class Knight : public NPC {
public:
    using NPC::NPC;
    NPCType type() const;
};