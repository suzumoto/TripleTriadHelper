#include <Rules.hpp>
#include <Board.hpp>
#include <CardData.hpp>
#include <string>
#include <gtest/gtest.h>

TEST(EvalTest, CASE1_Plus){
  enum CardID ally_card_list[5]{BloodSoul, TRexaur, Anacondaur, Tonberry, Trauma};
  enum CardID opponent_card_list[5]{TonberryKing, Malboro, Ochu, Jelleye, Gerogero};
  
  enum Player turn = Ally;
  Rules rule(true, false, false, false, true, false, false); // Plus
  
  Board test_board1(ally_card_list, opponent_card_list, rule, turn);
  
  test_board1.ForceCardOnBoard(Ally, 0, 0, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 1, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 2, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 3, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 4, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 5, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 6, Ally);
  test_board1.ForceCardOnBoard(Opponent, 1, 8, Ally);
  test_board1.SetTurn(Opponent);
  EXPECT_EQ(test_board1.MoveEval(0, 7), 1);
}

TEST(EvalTest, CASE2){
  enum CardID ally_card_list[5]{Squall, Seifer, Edea, Irvine, Doomtrain};
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  
  Rules rule(true, false, false, false, false, false, false);

  Board test_board(ally_card_list, opponent_card_list, rule, turn);
  test_board.Play(1,0);
  test_board.Play(0,1);
  test_board.Play(1,6);
  test_board.Play(0,3);
  test_board.Play(0,8);
  test_board.Play(0,4);
  std::cout << test_board << std::endl;
  EXPECT_EQ(test_board.MoveEval(0,2), 1);
}

TEST(EvalTest, CASE3){
  enum CardID ally_card_list[5]{Squall, Seifer, Edea, Irvine, Doomtrain};
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  
  Rules rule(true, false, false, false, false, false, false);

  Board test_board(ally_card_list, opponent_card_list, rule, turn);
  test_board.Play(1,0);
  test_board.Play(0,1);
  test_board.Play(1,6);
  test_board.Play(0,3);
  std::cout << test_board << std::endl;
  EXPECT_EQ(test_board.MoveEval(0,8), 1);
}

TEST(EvalTest, CASE4){
  enum CardID ally_card_list[5]{Squall, Seifer, Edea, Irvine, Doomtrain};
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  
  Rules rule(true, false, false, false, false, false, false);

  Board test_board(ally_card_list, opponent_card_list, rule, turn);
  test_board.Play(1,0);
  test_board.Play(0,1);
  std::cout << test_board << std::endl;
  EXPECT_EQ(test_board.MoveEval(1,6), 1);
}

TEST(EvalTest, CASE5){
  enum CardID ally_card_list[5]{Squall, Seifer, Edea, Irvine, Doomtrain};
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  
  Rules rule(true, false, false, false, false, false, false);

  Board test_board(ally_card_list, opponent_card_list, rule, turn);
  std::cout << test_board << std::endl;
  EXPECT_EQ(test_board.MoveEval(1,0), 1);
}

TEST(EvalTest, CASE6){
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  
  Rules rule(true, false, false, false, false, false, false);
  
  Board test_board(ally_card_list, opponent_card_list, rule, turn);
  std::cout << test_board << std::endl;
  long count = 0;
  EXPECT_EQ(test_board.MoveEval(1,0,count), 0);
  std::cout << "count = " << count << std::endl;
}

TEST(EvalTest, CASE7){
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum CardID opponent_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum Player turn = Ally;
  
  Rules rule(true, false, false, true, true, true, false);
  
  Board test_board(ally_card_list, opponent_card_list, rule, turn);
  std::cout << test_board << std::endl;
  long count = 0;
  EXPECT_EQ(test_board.MoveEval(1,0,count), 0);
  std::cout << "count = " << count << std::endl;
}
