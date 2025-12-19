#pragma once
#include "../npc/npc.hpp"
#include "visitor.hpp"

class BattleVisitor {
public:
    bool resolve(NPC& attacker, NPC& victim);
    bool static canKill(NPCType attacker, NPCType victim){
        if (attacker == NPCType::Knight) return victim == NPCType::Elf;
        if (attacker == NPCType::Elf) return victim == NPCType::Druid || victim == NPCType::Knight;
        if (attacker == NPCType::Druid)  return victim == NPCType::Druid;
        return false;
    }
    int static rollD6();
};
