#pragma once
#include <vector>
#include <memory>

class NPC;
class Knight;
class Druid;
class Elf;
class Observer;

class BattleVisitor {
private:
    std::vector<Observer*> observers;

public:
    BattleVisitor(std::vector<Observer*> observers);

    bool visit(const Knight& attacker, const NPC& other) const;
    bool visit(const Elf& attacker, const NPC& other) const;
    bool visit(const Druid& attacker, const NPC& other) const;

    static double dist(const NPC& a, const NPC& b);
    void fightUntilCan(std::vector<std::unique_ptr<NPC> >& npcs, double radius);
};
