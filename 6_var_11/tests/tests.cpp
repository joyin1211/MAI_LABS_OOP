#include <gtest/gtest.h>
#include "../src/npc/types.hpp"
#include "../src/npc/npc.hpp"
#include "../src/patterns/npc_factory.hpp"
#include "../src/editor/editor.hpp"

TEST(TypesTest, ToString) {
    EXPECT_EQ(toString(NPCType::Knight), "Knight");
    EXPECT_EQ(toString(NPCType::Druid),  "Druid");
    EXPECT_EQ(toString(NPCType::Elf),    "Elf");
}

TEST(TypesTest, ParseTypeValid) {
    auto k = parseType("Knight");
    auto d = parseType("Druid");
    auto e = parseType("Elf");

    ASSERT_TRUE(k.has_value());
    ASSERT_TRUE(d.has_value());
    ASSERT_TRUE(e.has_value());

    EXPECT_EQ(*k, NPCType::Knight);
    EXPECT_EQ(*d, NPCType::Druid);
    EXPECT_EQ(*e, NPCType::Elf);
}

TEST(TypesTest, ParseTypeInvalid) {
    EXPECT_FALSE(parseType("miau").has_value());
    EXPECT_FALSE(parseType("").has_value());
}

TEST(FactoryTest, CreateTypes) {
    auto k = NPCFactory::create(NPCType::Knight, "k1", 1, 2);
    auto d = NPCFactory::create(NPCType::Druid,  "d1", 3, 4);
    auto e = NPCFactory::create(NPCType::Elf,    "e1", 5, 6);

    ASSERT_NE(k, nullptr);
    ASSERT_NE(d, nullptr);
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(k->type(), NPCType::Knight);
    EXPECT_EQ(d->type(), NPCType::Druid);
    EXPECT_EQ(e->type(), NPCType::Elf);

    EXPECT_EQ(k->getName(), "k1");
    EXPECT_DOUBLE_EQ(k->getX(), 1);
    EXPECT_DOUBLE_EQ(k->getY(), 2);
}


TEST(Editor, UniqueNameWithinType) {
    Editor ed;
    ed.addNPC(NPCType::Knight, "A", 10, 10);
    EXPECT_THROW(ed.addNPC(NPCType::Knight, "A", 20, 20), std::invalid_argument);
    EXPECT_NO_THROW(ed.addNPC(NPCType::Elf, "A", 30, 30));
}

TEST(Editor, CoordsRange) {
    Editor ed;
    EXPECT_THROW(ed.addNPC(NPCType::Elf, "e1", -1, 0), std::invalid_argument);
    EXPECT_THROW(ed.addNPC(NPCType::Elf, "e2", 0, 501), std::invalid_argument);
    EXPECT_NO_THROW(ed.addNPC(NPCType::Elf, "e3", 0, 0));
    EXPECT_NO_THROW(ed.addNPC(NPCType::Elf, "e4", 500, 500));
}