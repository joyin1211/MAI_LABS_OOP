#include "npc_factory.hpp"
#include "../npc/npc.hpp"
#include "../npc/knight.hpp"
#include "../npc/druid.hpp"
#include "../npc/elf.hpp"
#include "../npc/types.hpp"
#include <sstream>
#include <stdexcept>

std::unique_ptr<NPC> NPCFactory::create(NPCType t, const std::string& name, double x, double y) {
    switch (t) {
        case NPCType::Knight: return std::make_unique<Knight>(name, x, y);
        case NPCType::Druid: return std::make_unique<Druid>(name, x, y);
        case NPCType::Elf: return std::make_unique<Elf>(name, x, y);
        default: throw std::invalid_argument("Unknown type");
    }
}

std::unique_ptr<NPC> NPCFactory::fromLine(const std::string& line) {
    std::istringstream iss(line);
    std::string type, name;
    double x, y;
    if (!(iss >> type >> name >> x >> y)) {
        throw std::runtime_error("Bad line: " + line);
    }
    auto t = parseType(type);
    if (!t) {
        throw std::invalid_argument("Unknown type in file: " + type);
    }
    return create(*t, name, x, y);
}
