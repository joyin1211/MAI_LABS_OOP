#include "npc.hpp"

NPC::NPC(int id, std::string name, double x, double y, int move_distance, int kill_distance) :
 id(id), name(std::move(name)), x(x), y(y), move_distance(move_distance), kill_distance(kill_distance) {}

const std::string& NPC::getName() const { return name; }
double NPC::getX() const { return x; }
double NPC::getY() const { return y; }
int NPC::getId() const { return id; }
void NPC::setX(double x) {
    this->x = x;
}
void NPC::setY(double y) {
    this->y = y;
}
void NPC::setAlive(bool f) {
    alive = f;
}
int NPC::getMoveDistance() const {return move_distance;}
int NPC::getKillDistance() const {return kill_distance;}
bool NPC::getAlive() const {return alive;}
