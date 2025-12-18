#include "elf.hpp"
#include "../patterns/battle_visitor.hpp"

NPCType Elf::type() const {
    return NPCType::Elf;
}

bool Elf::accept(BattleVisitor& v, const NPC& other) const {
    return v.visit(*this, other);
}