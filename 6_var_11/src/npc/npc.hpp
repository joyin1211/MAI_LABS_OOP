#pragma once
#include <string>
#include "types.hpp"

class BattleVisitor;

class NPC {

protected:
    std::string name;
    double x{};
    double y{};
    
public:
    NPC(std::string name, double x, double y);
    virtual ~NPC() = default;

    virtual NPCType type() const = 0;
    virtual bool accept(BattleVisitor& v, const NPC& other) const = 0;

    const std::string& getName() const;
    double getX() const;
    double getY() const;
};
