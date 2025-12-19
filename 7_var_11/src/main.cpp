#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>

#include "editor/editor.hpp"
#include "patterns/movement_visitor.hpp"
#include "patterns/battle_visitor.hpp"
#include "patterns/dispatch_queue.hpp"
#include "render.hpp"

int main() {
    using namespace std::chrono_literals;
    const int W = 20, H = 20;
    Editor editor(W, H);
    editor.initRandom(50);

    MovementVisitor movementVisitor(W, H);
    BattleVisitor battleVisitor;

    DispatchQueue<BattleTask> battleQueue;

    std::atomic<bool> stop{false};

    battleQueue.start([&](const BattleTask& task) {
        editor.resolveBattleTask(task, battleVisitor);
    });

    std::thread mover([&] {
        while (!stop.load()) {
            editor.movementTick(movementVisitor);
            editor.detectBattles(battleQueue);
            std::this_thread::sleep_for(100ms);
        }
    });
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < 30s) {
        auto snapshot = editor.snapshotAlive();
        {
            std::lock_guard<std::mutex> lg(editor.coutMutex());
            std::cout << renderMap(snapshot, H, W) << std::flush;
        }

        std::this_thread::sleep_for(1s);
    }

    stop.store(true);
    mover.join();

    battleQueue.stop();
    std::lock_guard<std::mutex> lg(editor.coutMutex());
    std::cout << "\n=== SURVIVORS ===\n";
    for (const auto& s : editor.survivorsList()) {
        std::cout << s << "\n";
    }

    return 0;
}