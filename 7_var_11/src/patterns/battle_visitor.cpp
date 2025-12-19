#include "visitor.hpp"
#include "battle_visitor.hpp"
#include <random>
#include <chrono>

bool BattleVisitor::resolve(NPC& attacker, NPC& defender) {
    if (!attacker.getAlive() || !defender.getAlive()) return false;
    if (!canKill(attacker.type(), defender.type())) return false;

    int atk = rollD6();
    int def = rollD6();

    if (atk > def) {
        defender.setAlive(false);
        return true;
    }
    return false;
}

int BattleVisitor::rollD6() {
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    return rnd() % 6;
}
