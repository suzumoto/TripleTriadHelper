#include <Board.hpp>

#include <gtest/gtest.h>

TEST(DynamicTest, CASE1_DYNAMIC){
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
    
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  Rules rule(true, false, false, false, false, false, false);
  CardData card_data;
  
  Board test_board1(ally_card_list, opponent_card_list, rule, turn, card_data);
  std::unordered_map<long, int> already_searched_list;
  EXPECT_EQ(test_board1.MoveEval(1, 0, already_searched_list), 0);
}

TEST(DynamicTest, CASE2_STATIC){
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
    
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  Rules rule(true, false, false, false, false, false, false);
  CardData card_data;
  
  Board test_board1(ally_card_list, opponent_card_list, rule, turn, card_data);
  EXPECT_EQ(test_board1.MoveEval(1, 0), 0);
}
