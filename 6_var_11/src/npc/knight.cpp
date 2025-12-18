#include "knight.hpp"
#include "../patterns/battle_visitor.hpp"

NPCType Knight::type() const {
    return NPCType::Knight;
}

bool Knight::accept(BattleVisitor& v, const NPC& other) const {
    return v.visit(*this, other);
}