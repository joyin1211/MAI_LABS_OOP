#pragma once
#include "../npc/npc.hpp"

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(NPC& npc) = 0;

};