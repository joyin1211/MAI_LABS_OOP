#include <iostream>
#include "npc/types.hpp"
#include "editor/editor.hpp"

int main() {

    Editor ed;
    std::cout << "Commands:\n"
              << "  add <Knight|Druid|Elf> <name> <x> <y>\n"
              << "  list\n"
              << "  save <file.txt>\n"
              << "  load <file.txt>\n"
              << "  battle <radius>\n"
              << "  exit" << std::endl;

    std::string cmd;
    while (true) {
        std::cout << "> ";
        if (!(std::cin >> cmd)) break;

        try {
            if (cmd == "add") {
                std::string ts, name;
                double x, y;
                std::cin >> ts >> name >> x >> y;
                auto t = parseType(ts);
                if (!t) throw std::invalid_argument("Unknown type: " + ts);
                ed.addNPC(*t, name, x, y);
            } else if (cmd == "list") {
                ed.listNPCs();
            } else if (cmd == "save") {
                std::string file; std::cin >> file;
                ed.save(file);
            } else if (cmd == "load") {
                std::string file; std::cin >> file;
                ed.load(file);
            } else if (cmd == "battle") {
                double r; std::cin >> r;
                ed.battle(r);
            } else if (cmd == "exit") {
                break;
            } else {
                std::cout << "Unknown command." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
