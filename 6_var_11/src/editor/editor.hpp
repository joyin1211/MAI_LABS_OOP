#include <vector>
#include <memory>
#include <map>
#include <set>
#include <string>
#include "../npc/types.hpp"

class NPC;

class Editor {
private:
    static void checkCoords(double x, double y);
    void rebuildNameIndex();

    std::vector<std::unique_ptr<NPC>> npcs;
    std::map<NPCType, std::set<std::string>> namesByType;
public:
    Editor();
    ~Editor();
    void addNPC(NPCType t, const std::string& name, double x, double y);
    void listNPCs() const;

    void save(const std::string& path) const;
    void load(const std::string& path);

    void battle(double radius);
};
