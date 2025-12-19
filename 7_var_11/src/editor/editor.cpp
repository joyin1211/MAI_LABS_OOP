#include "editor.hpp"
#include "../patterns/npc_factory.hpp"
#include "../patterns/battle_visitor.hpp"
#include "../patterns/movement_visitor.hpp"
#include <random>
#include <cmath>
#include <shared_mutex>

Editor::Editor(int w, int h)
    : consoleObs(cout_mutex), W(w), H(h)
{
    observers.push_back(&consoleObs);
    observers.push_back(&fileObs);
}

std::mutex& Editor::coutMutex() { return cout_mutex; }

void Editor::initRandom(int count) {
    std::lock_guard<std::shared_mutex> lg(npcs_mutex);

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> posX(0, W - 1);
    std::uniform_int_distribution<int> posY(0, H - 1);
    std::uniform_int_distribution<int> typeDist(0, 2);

    int k = 0, d = 0, e = 0;
    for (int i = 0; i < count; ++i) {
        NPCType t = static_cast<NPCType>(typeDist(gen));
        std::string name =
            (t == NPCType::Knight ? "K" + std::to_string(++k) :
             t == NPCType::Druid  ? "D" + std::to_string(++d) :
                                    "E" + std::to_string(++e));
        npcs.push_back(NPCFactory::create(i, t, name, posX(gen), posY(gen)));
    }
}

std::vector<Editor::Snap> Editor::snapshotAlive() const {
    std::shared_lock<std::shared_mutex> sl(npcs_mutex);
    std::vector<Snap> snap;
    for (auto const& n : npcs){
        if (n->getAlive()) { 
            snap.push_back({n->type(), n->getX(), n->getY(), n->getName(), n->getId()});
        }
    }
    return snap;
}



bool Editor::withinKillDistance(const NPC& a, const NPC& b) const {
    return std::max(std::abs(a.getX() - b.getX()), std::abs(a.getY() - b.getY()))
           <= std::max(a.getKillDistance(), b.getKillDistance());
}

std::shared_ptr<NPC> Editor::findById(int id) {
    if (id < 0 || id >= (int)npcs.size()){
        return nullptr;
    }
    return npcs[id];
}

void Editor::movementTick(MovementVisitor& mv) {
    std::lock_guard<std::shared_mutex> lg(npcs_mutex);
    for (auto& npc : npcs)
        mv.visit(*npc);
}

void Editor::detectBattles(DispatchQueue<BattleTask>& dq) {
    std::lock_guard<std::shared_mutex> lg(npcs_mutex);
    for (size_t i = 0; i < npcs.size(); ++i)
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            auto& a = npcs[i];
            auto& b = npcs[j];
            if (!a->getAlive() || !b->getAlive()) {
                continue;
            }
            if (!withinKillDistance(*a, *b)) {
                continue;
            }
            dq.dispatch({a->getId(), b->getId()});
        }
}


void Editor::resolveBattleTask(const BattleTask& task, BattleVisitor bv) {
    std::lock_guard<std::shared_mutex> lg(npcs_mutex);

    std::shared_ptr<NPC> attacker = findById(task.attackerId);
    std::shared_ptr<NPC> defender = findById(task.defenderId);
    if (!attacker || !defender) return;

    bool killed = bv.resolve(*attacker, *defender);
    if (killed)
        for (auto* o : observers){
             o->onKill(*attacker, *defender);
        }
}

std::vector<std::string> Editor::survivorsList() const {
    std::shared_lock<std::shared_mutex> sl(npcs_mutex);
    std::vector<std::string> res;
    for (auto const& n : npcs){
        if (n->getAlive()){
            res.push_back(toString(n->type()) + "(" + n->getName() + ")");
        }
    }
    return res;
}
