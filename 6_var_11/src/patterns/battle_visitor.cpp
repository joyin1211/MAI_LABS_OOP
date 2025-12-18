#include "battle_visitor.hpp"
#include "observer.hpp"
#include "../npc/npc.hpp"
#include "../npc/types.hpp"
#include "../npc/knight.hpp"
#include "../npc/elf.hpp"
#include "../npc/druid.hpp"
#include <cmath>
#include <iostream>

BattleVisitor::BattleVisitor(std::vector<Observer*> observers)
    : observers(std::move(observers)) {}

bool BattleVisitor::visit(const Knight& first, const NPC& second) const {
    return second.type() == NPCType::Elf;
}
bool BattleVisitor::visit(const Elf& first, const NPC& second) const {
    return second.type() == NPCType::Druid || second.type() == NPCType::Knight;
}
bool BattleVisitor::visit(const Druid& first, const NPC& second) const {
    return second.type() == NPCType::Druid;
}

double BattleVisitor::dist(const NPC& a, const NPC& b) {
    double dx = a.getX() - b.getX();
    double dy = a.getY() - b.getY();
    return std::sqrt(dx * dx + dy * dy);
}

void BattleVisitor::fightUntilCan(std::vector<std::unique_ptr<NPC> >& npcs, double radius) {
    while (true) {
        std::vector<std::pair<const NPC*, const NPC*> > kills;
        std::vector<bool> dead(npcs.size(), 0);
        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                const NPC& a = *npcs[i];
                const NPC& b = *npcs[j];
                if (dist(a, b) > radius)  {
                    continue;
                }
                bool aKillsB = a.accept(*this, b);
                bool bKillsA = b.accept(*this, a);
                if (aKillsB) {
                    kills.push_back({&a, &b});
                    dead[j] = true;
                }
                if (bKillsA) {
                    kills.push_back({&b, &a});
                    dead[i] = true;
                }
            }
        }
        if (kills.empty()) {
            break;
        }
        for (auto& kill : kills) {
            for (auto* obs : observers) {
                obs->onKill(*kill.first, *kill.second);
            }
        }
        std::vector<std::unique_ptr<NPC> > alive;
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!dead[i]) {
                alive.push_back(std::move(npcs[i]));
            }
        }
        npcs = std::move(alive);
    }
}
