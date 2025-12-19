#pragma once
#include <string>
#include <optional>

enum class NPCType { Knight, Druid, Elf };

inline std::string toString(NPCType t) {
    switch (t) {
        case NPCType::Knight: return "Knight";
        case NPCType::Druid:  return "Druid";
        case NPCType::Elf:    return "Elf";
        default: return "Unknown";
    }
}

inline std::optional<NPCType> parseType(const std::string& s) {
    if (s == "Knight") return NPCType::Knight;
    if (s == "Druid")  return NPCType::Druid;
    if (s == "Elf")    return NPCType::Elf;
    return std::nullopt;
}

static char toChar(NPCType t) {
    switch (t) {
        case NPCType::Knight: return 'K';
        case NPCType::Druid:  return 'D';
        case NPCType::Elf:    return 'E';
    }
    return '?';
}