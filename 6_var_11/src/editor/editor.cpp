#include "editor.hpp"
#include "../npc/npc.hpp"
#include "../npc/types.hpp"
#include "../patterns/npc_factory.hpp"
#include "../patterns/battle_visitor.hpp"
#include "../patterns/observer.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdexcept>


Editor::Editor() = default;
Editor::~Editor() = default;

void Editor::checkCoords(double x, double y) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::invalid_argument("Coordinates must be in range [0, 500]");
    }
}

void Editor::rebuildNameIndex() {
    namesByType.clear();
    for (auto& p : npcs) {
        namesByType[p->type()].insert(p->getName());
    }
}

void Editor::addNPC(NPCType t, const std::string& name, double x, double y) {
    checkCoords(x, y);
    if (namesByType[t].find(name) != namesByType[t].end()) {
        throw std::invalid_argument("Name '" + name + "' already used for this type.");
    }
    npcs.push_back(NPCFactory::create(t, name, x, y));
    namesByType[t].insert(name);
}

void Editor::listNPCs() const {
    if (npcs.empty()) { std::cout << "(empty)\n"; return; }
    for (auto& p : npcs) {
        std::cout << std::setw(6) << toString(p->type())
                  << "  name=" << p->getName()
                  << "  x=" << std::fixed << std::setprecision(2) << p->getX()
                  << "  y=" << std::fixed << std::setprecision(2) << p->getY() << "\n";
    }
}

void Editor::save(const std::string& path) const {
    std::ofstream out(path);
    if (!out) {
        throw std::invalid_argument("Cannot open file for write: " + path);
    }
    for (auto& p : npcs) {
        out << toString(p->type()) << " " << p->getName() << " " << p->getX() << " " << p->getY() << "\n";
    }
}

void Editor::load(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::invalid_argument("Cannot open file for read: " + path);
    }

    std::vector<std::unique_ptr<NPC>> loaded;
    std::map<NPCType, std::set<std::string>> newIndex;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        auto npc = NPCFactory::fromLine(line);
        checkCoords(npc->getX(), npc->getY());
        if (newIndex[npc->type()].count(npc->getName())) {
            throw std::invalid_argument("Duplicate name '" + npc->getName() + "' for type " + toString(npc->type()) + " in file.");
        }
        newIndex[npc->type()].insert(npc->getName());
        loaded.push_back(std::move(npc));
    }
    npcs = std::move(loaded);
    namesByType = std::move(newIndex);
}

void Editor::battle(double radius) {
    ConsoleObserver consoleObs;
    FileObserver fileObs;
    std::vector<Observer*> obs;
    obs.push_back(&consoleObs);
    obs.push_back(&fileObs);
    BattleVisitor visitor(obs);
    visitor.fightUntilCan(npcs, radius);
    rebuildNameIndex();
}
