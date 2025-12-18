#pragma once
#include "npc.hpp"
#include <string>

class Druid : public NPC {
public:
    using NPC::NPC;
    NPCType type() const;
    bool accept(BattleVisitor& v, const NPC& other) const;
};