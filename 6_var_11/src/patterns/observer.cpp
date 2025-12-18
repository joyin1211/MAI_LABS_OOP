#include "observer.hpp"
#include "../npc/npc.hpp"
#include "../npc/types.hpp"
#include <iostream>
#include <fstream>

void ConsoleObserver::onKill(const NPC& killer, const NPC& victim) {
    std::cout << toString(killer.type()) << "(" << killer.getName() << ") убивает "
              << toString(victim.type()) << "(" << victim.getName() << ")\n";
}

void FileObserver::onKill(const NPC& killer, const NPC& victim) {
    std::ofstream out(path, std::ios::app);
    out << toString(killer.type()) << "(" << killer.getName() << ") убивает "
        << toString(victim.type()) << "(" << victim.getName() << ")\n";
    out.close();
}
