#include <Config.h>

#ifdef MAD_ENGINE_ENABLE_UNIT_TESTS
#include <GlobalEventsDeck.h>
#include <gtest/gtest.h>

class GlobalEventsDeckUnitTests : public testing::Test {

};

TEST_F(GlobalEventsDeckUnitTests, ShouldStartWithPopulationGrowthAndEndsWithMilitaryCampaignAgainstPersia) {

	GlobalEventsDeck deck;
	deck.Reset(true);

	auto v = deck.Next();
	deck.AddToOpen(std::get<0>(v));
	EXPECT_EQ(GlobalEventType::PopulationGrowth, std::get<0>(v));

	for (int i = 0; i < 7;++i){
		EXPECT_TRUE(deck.CanTake());
		auto p = deck.Next();		
		deck.AddToOpen(std::get<0>(p));
	}

	EXPECT_TRUE(deck.CanTake());
	v = deck.Next();
	deck.AddToOpen(std::get<0>(v));
	EXPECT_FALSE(deck.CanTake());

	EXPECT_EQ(GlobalEventType::MilitaryCampaignAgainstPersia, std::get<0>(v));
}

#endif

