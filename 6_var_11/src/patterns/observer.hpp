#pragma once
#include <string>

class NPC;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onKill(const NPC& killer, const NPC& victim) = 0;
};

class ConsoleObserver : public Observer {
public:
    void onKill(const NPC& killer, const NPC& victim) override;
};

class FileObserver : public Observer {
private:
    std::string path = "../logs/log.txt";
public:
    void onKill(const NPC& killer, const NPC& victim) override;
};
