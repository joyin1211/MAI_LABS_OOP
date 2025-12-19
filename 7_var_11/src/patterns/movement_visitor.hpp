#pragma once
#include "visitor.hpp"
#include "../npc/npc.hpp"

class MovementVisitor : public Visitor {
public:
    const int W;
    const int H;
    MovementVisitor(int w, int h);
    void visit(NPC& npc) override;

private:
    void clamp(NPC& npc) const;
};