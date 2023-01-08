#include <Config.h>

#ifdef MAD_ENGINE_ENABLE_UNIT_TESTS
#include <PoliciesDeck.h>
#include <gtest/gtest.h>

class PoliciesDeckTest : public testing::Test {

};

TEST_F(PoliciesDeckTest, TakeFromDeck) {

	PoliciesDeck deck;
	deck.Reset(false);


	for (int i = 0; i < deck.Size(); ++i) {
		EXPECT_TRUE(deck.CanTake());
		auto p = deck.Next();
		EXPECT_EQ((Policies)(deck.Size() - i - 1), std::get<0>(p));
		EXPECT_EQ((deck.Size() - i - 1), std::get<1>(p));
	}

	EXPECT_FALSE(deck.CanTake());
}

TEST_F(PoliciesDeckTest, TakeAllDropOne) {

	PoliciesDeck deck;
	deck.Reset(false);


	for (int i = 0; i < deck.Size(); ++i) {
		EXPECT_TRUE(deck.CanTake());
		auto p = deck.Next();
		EXPECT_EQ((Policies)(deck.Size() - i - 1), std::get<0>(p));
		EXPECT_EQ((deck.Size() - i - 1), std::get<1>(p));
	}

	EXPECT_FALSE(deck.CanTake());

	deck.Drop(Policies::policy_front_archives);

	EXPECT_TRUE(deck.CanTake());
	auto p = deck.Next();
	EXPECT_EQ(Policies::policy_front_archives, std::get<0>(p));
	EXPECT_EQ(0, std::get<1>(p));

	EXPECT_FALSE(deck.CanTake());
}

TEST_F(PoliciesDeckTest, DropFromDeck) {

	PoliciesDeck deck;
	deck.Reset(false);

	EXPECT_TRUE(deck.CanTake());
	auto v = deck.Next();

	EXPECT_EQ((Policies)(deck.Size() - 1), std::get<0>(v));

	deck.Drop(std::get<0>(v));	
}

#endif

