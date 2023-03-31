#include <Rules.hpp>
#include <Board.hpp>
#include <CardData.hpp>

#include <chrono>
#include <string>
#include <gtest/gtest.h>

TEST(PlayTest, CASE1){
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
    
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  Rules rule(true, false, false, false, false, false, false);

  Board test_board1(ally_card_list, opponent_card_list, rule, turn);
  Board test_board2(ally_card_list, opponent_card_list, rule, turn);
  ASSERT_EQ(test_board1, test_board2);
}

TEST(PlayTest, CASE2){
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
    
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  Rules rule(true, false, false, false, false, false, false);

  Board test_board1(ally_card_list, opponent_card_list, rule, turn);
  Board test_board2(ally_card_list, opponent_card_list, rule, turn);
  test_board1.Play(0, 0);
  EXPECT_EQ(test_board1, test_board2);
}

TEST(PlayTest, CASE3){
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
    
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  Rules rule(true, false, false, false, false, false, false);

  Board test_board1(ally_card_list, opponent_card_list, rule, turn);
  Board test_board2(ally_card_list, opponent_card_list, rule, turn);
  test_board1.Play(0, 0);
  try{
    test_board1.Play(0, 1);
  }
  catch(std::runtime_error& e){
    std::string error(e.what());
    EXPECT_EQ(error, "dne");
  }
  EXPECT_EQ(test_board1, test_board2);
}


