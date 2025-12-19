#include "movement_visitor.hpp"
#include <random>
#include <algorithm>
#include <chrono>
#include <vector>

MovementVisitor::MovementVisitor(int w, int h) : W(w), H(h) {};

void MovementVisitor::visit(NPC& npc) {
    if (!npc.getAlive()) {
        return;
    }
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    int step = npc.getMoveDistance();
    std::vector<std::pair<int, int> > directions = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    int move_id = rnd() % 4;
    npc.setX(npc.getX() + directions[move_id].first);
    npc.setY(npc.getY() + directions[move_id].second);
    clamp(npc);
}

void MovementVisitor::clamp(NPC& npc) const {
    npc.setX(std::max((double)0, std::min((double)W - 1, npc.getX())));
    npc.setY(std::max((double)0, std::min((double)H - 1, npc.getY())));
}
