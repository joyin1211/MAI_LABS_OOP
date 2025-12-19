#pragma once
#include <vector>
#include <shared_mutex>
#include <mutex>
#include <string>

#include "../npc/npc.hpp"
#include "../patterns/visitor.hpp"
#include "../patterns/observer.hpp"
#include "../patterns/movement_visitor.hpp"
#include "../patterns/dispatch_queue.hpp"

struct BattleTask {
    int attackerId;
    int defenderId;
};

class Editor {
public:
    int W;
    int H;

    Editor(int w, int h);

    void initRandom(int count);

    struct Snap { NPCType type; double x; double y; std::string name; int id; };
    std::vector<Snap> snapshotAlive() const;

    void movementTick(MovementVisitor& mv);
    void detectBattles(DispatchQueue<BattleTask>& dq);
    void resolveBattleTask(const BattleTask& task, BattleVisitor bv);

    std::vector<std::string> survivorsList() const;
    std::mutex& coutMutex();

private:
    int moveStep(NPCType t) const;
    int killDistance(NPCType t) const;
    bool withinKillDistance(const NPC& a, const NPC& b) const;
    std::shared_ptr<NPC> findById(int id);
    mutable std::shared_mutex npcs_mutex;
    std::vector<std::shared_ptr<NPC>> npcs;
    std::mutex cout_mutex;
    ConsoleObserver consoleObs;
    FileObserver fileObs;
    std::vector<Observer*> observers;
};
