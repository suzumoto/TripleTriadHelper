#include <Board.hpp>

#include <gtest/gtest.h>

TEST(HashTest, CASE1){
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
    
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  Rules rule(true, false, false, false, false, false, false);
  CardData card_data;
  Board test_board1(ally_card_list, opponent_card_list, rule, turn, card_data);
  test_board1.Play(0,0);
  test_board1.Play(0,1);
  test_board1.Play(0,2);
  test_board1.Play(0,3);

  Board test_board2(ally_card_list, opponent_card_list, rule, turn, card_data);
  test_board2.Play(1,2);
  test_board2.Play(0,1);
  test_board2.Play(0,0);
  test_board2.Play(0,3);
  EXPECT_NE(test_board1.GetBoardHash(), test_board2.GetBoardHash());
}
