#pragma once
#include <string>
#include "types.hpp"

class BattleVisitor;

class NPC {

protected:
    std::string name;
    int id;
    int move_distance{};
    int kill_distance{};
    bool alive{true};
    double x{};
    double y{};
    
public:
    NPC(int id, std::string name, double x, double y, int move_distance, int kill_distance);
    virtual ~NPC() = default;

    virtual NPCType type() const = 0;

    const std::string& getName() const;
    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);
    bool getAlive() const;
    void setAlive(bool f);
    int getId() const;
    int getMoveDistance() const;
    int getKillDistance() const;
};
