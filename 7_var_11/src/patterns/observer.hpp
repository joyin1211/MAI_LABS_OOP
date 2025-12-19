#pragma once
#include <string>
#include <mutex>

class NPC;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onKill(const NPC& killer, const NPC& victim) = 0;
};

class ConsoleObserver : public Observer {
private:
    std::mutex& cout_mutex;
public:
    ConsoleObserver(std::mutex &cout_mutex);
    void onKill(const NPC& killer, const NPC& victim) override;
};

class FileObserver : public Observer {
private:
    std::string path = "../logs/log.txt";
public:
    void onKill(const NPC& killer, const NPC& victim) override;
};
