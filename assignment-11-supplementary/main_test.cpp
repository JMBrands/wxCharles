#include "main.cpp"
#include "gtest/gtest.h"

TEST(assignment, desktop)
{
  EXPECT_TRUE(match_pattern("hu.t", "hurt"));
  EXPECT_TRUE(match_pattern("hu.t", "hunt"));
  EXPECT_FALSE(match_pattern("hu.t", "hut"));
  EXPECT_FALSE(match_pattern("hu.t", "hunts"));
  EXPECT_TRUE(match_pattern("Cu*e", "Cue"));
  EXPECT_TRUE(match_pattern("Cu*e", "Cure"));
  EXPECT_TRUE(match_pattern("Cu*e", "Curve"));
  EXPECT_FALSE(match_pattern("Cu*e", "A Cue"));
  EXPECT_FALSE(match_pattern("Cu*e", "A Cure"));
  EXPECT_FALSE(match_pattern("Cu*e", "A Curve"));
  EXPECT_TRUE(match_pattern("*ea*", "Dream Theater"));
}

TEST(assignment, pattern_dots)
{
  EXPECT_TRUE(match_pattern(".arbon", "carbon"));
  EXPECT_TRUE(match_pattern("c.urtesy", "courtesy"));
  EXPECT_TRUE(match_pattern("discover.", "discovery"));
  EXPECT_FALSE(match_pattern("c.p", "chop"));
  EXPECT_FALSE(match_pattern(".perfect", "perfect"));
  EXPECT_FALSE(match_pattern("discover.", "discover"));
  EXPECT_FALSE(match_pattern(".", ""));
  EXPECT_FALSE(match_pattern("..", ""));
}

TEST(assignment, pattern_stars)
{
  EXPECT_TRUE(match_pattern("*", "policeman"));
  EXPECT_TRUE(match_pattern("**", "misplace"));
  EXPECT_TRUE(match_pattern("*damage", "damage"));
  EXPECT_TRUE(match_pattern("*amage", "damage"));
  EXPECT_TRUE(match_pattern("*mage", "damage"));
  EXPECT_TRUE(match_pattern("qualified*", "qualified"));
  EXPECT_TRUE(match_pattern("qualifie*", "qualified"));
  EXPECT_TRUE(match_pattern("qualifi*", "qualified"));
  EXPECT_TRUE(match_pattern("concen*trate", "concentrate"));
  EXPECT_TRUE(match_pattern("conce*trate", "concentrate"));
  EXPECT_TRUE(match_pattern("conce*rate", "concentrate"));
  EXPECT_TRUE(match_pattern("*", ""));
  EXPECT_FALSE(match_pattern("*left", "let"));
  EXPECT_FALSE(match_pattern("left*", "let"));
  EXPECT_FALSE(match_pattern("le*ft", "let"));
}

TEST(assignment, pattern_dots_stars)
{
  EXPECT_TRUE(match_pattern(".*nsistence", "insistence"));
  EXPECT_TRUE(match_pattern(".*.*ductor", "conductor"));
  EXPECT_TRUE(match_pattern("...*cratic", "democratic"));
  EXPECT_TRUE(match_pattern("d.m*.*e", "damage"));
  EXPECT_FALSE(match_pattern("d.m*.*e", "dame"));
  EXPECT_TRUE(match_pattern("*.*.*.*", "eliminate"));
  EXPECT_TRUE(match_pattern("..**", "registration"));
  EXPECT_FALSE(match_pattern(".*", ""));
}
