#pragma once
#include "npc.hpp"
#include <string>

class Elf : public NPC {
public:
    using NPC::NPC;
    NPCType type() const;
};