#include "npc.hpp"

NPC::NPC(std::string name, double x, double y) : name(std::move(name)), x(x), y(y) {}

const std::string& NPC::getName() const { return name; }
double NPC::getX() const { return x; }
double NPC::getY() const { return y; }
