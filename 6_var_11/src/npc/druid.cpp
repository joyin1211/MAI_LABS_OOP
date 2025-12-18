#include "druid.hpp"
#include "../patterns/battle_visitor.hpp"

NPCType Druid::type() const {
    return NPCType::Druid;
}

bool Druid::accept(BattleVisitor& v, const NPC& other) const {
    return v.visit(*this, other);
}