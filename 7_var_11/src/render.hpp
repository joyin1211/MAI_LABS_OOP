#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "editor/editor.hpp"
#include "npc/types.hpp"

inline std::string renderMap(const std::vector<Editor::Snap>& snap, int H, int W) {
    std::vector<std::vector<std::string> > grid(H, std::vector<std::string>(W, "."));
    for (auto const& s : snap)
        grid[s.y][s.x] = s.name;

    std::ostringstream oss;
    oss << "=== MAP ===\n";
    for (auto& row : grid) {
        for (auto &cell : row) {
            oss << cell << " ";
        }
        oss << "\n";
    }
    return oss.str();
}