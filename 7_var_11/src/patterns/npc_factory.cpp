#include "npc_factory.hpp"
#include "../npc/npc.hpp"
#include "../npc/knight.hpp"
#include "../npc/druid.hpp"
#include "../npc/elf.hpp"
#include "../npc/types.hpp"
#include <sstream>
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::create(int id, NPCType t, const std::string& name, double x, double y) {
    switch (t) {
        case NPCType::Knight: return std::make_shared<Knight>(id, name, x, y, 30, 10);
        case NPCType::Druid: return std::make_shared<Druid>(id, name, x, y, 10, 10);
        case NPCType::Elf: return std::make_shared<Elf>(id, name, x, y, 10, 50);
        default: throw std::invalid_argument("Unknown type");
    }
}

