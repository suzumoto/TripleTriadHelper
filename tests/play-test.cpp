#include <Rules.hpp>
#include <Board.hpp>
#include <CardData.hpp>

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
  test_board2.ForceCardOnBoard(Ally, 0, 0, Ally);
  test_board2.SetTurn(Opponent);
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
  test_board1.Play(1, 3);
  test_board2.ForceCardOnBoard(Ally, 0, 0, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 1, 3, Opponent);
  EXPECT_EQ(test_board1, test_board2);
}

TEST(PlayTest, CASE4_Plus){
  enum CardID ally_card_list[5]{BloodSoul, TRexaur, Anacondaur, Tonberry, Trauma};
  enum CardID opponent_card_list[5]{TonberryKing, Malboro, Ochu, Jelleye, Gerogero};

  enum Player turn = Ally;
  Rules rule(true, false, false, false, true, false, false); // Plus
  
  Board test_board1(ally_card_list, opponent_card_list, rule, turn);
  Board test_board2(ally_card_list, opponent_card_list, rule, turn);

  test_board1.ForceCardOnBoard(Ally, 0, 0, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 1, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 2, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 3, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 4, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 5, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 6, Ally);
  test_board1.ForceCardOnBoard(Opponent, 1, 8, Ally);
  test_board1.SetTurn(Opponent);
  test_board1.Play(0, 7);

  test_board2.ForceCardOnBoard(Ally, 0, 0, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 1, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 2, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 3, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 4, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 5, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 6, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 1, 8, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 7, Opponent);
  EXPECT_EQ(test_board1, test_board2);
  EXPECT_EQ(test_board1.GetWinner(), Opponent);
}

TEST(PlayTest, CASE5_Same){
  enum CardID ally_card_list[5]{BloodSoul, TRexaur, Anacondaur, Tonberry, Trauma};
  enum CardID opponent_card_list[5]{TonberryKing, Malboro, BGH251F2, Jelleye, Gerogero};

  enum Player turn = Ally;
  Rules rule(true, false, false, true, false, false, false); // Same
  
  Board test_board1(ally_card_list, opponent_card_list, rule, turn);
  Board test_board2(ally_card_list, opponent_card_list, rule, turn);

  test_board1.ForceCardOnBoard(Ally, 0, 0, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 1, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 2, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 3, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 4, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 5, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 6, Ally);
  test_board1.ForceCardOnBoard(Opponent, 1, 8, Ally);
  test_board1.SetTurn(Opponent);
  test_board1.Play(0, 7);

  test_board2.ForceCardOnBoard(Ally, 0, 0, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 1, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 2, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 3, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 4, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 5, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 6, Ally);
  test_board2.ForceCardOnBoard(Opponent, 1, 8, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 7, Opponent);
  EXPECT_EQ(test_board1, test_board2);
  EXPECT_EQ(test_board1.GetWinner(), Opponent);
}

TEST(PlayTest, CASE6_WallSame){
  enum CardID ally_card_list[5]{BloodSoul, TRexaur, Anacondaur, Tonberry, Trauma};
  enum CardID opponent_card_list[5]{TonberryKing, Malboro, Zell, BGH251F2, Gerogero};

  enum Player turn = Ally;
  Rules rule(true, false, false, true, false, true, false); // Same and WallSame
  
  Board test_board1(ally_card_list, opponent_card_list, rule, turn);
  Board test_board2(ally_card_list, opponent_card_list, rule, turn);

  test_board1.ForceCardOnBoard(Ally, 0, 0, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 1, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 2, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 3, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 4, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 5, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 6, Ally);
  test_board1.ForceCardOnBoard(Opponent, 1, 8, Ally);
  test_board1.SetTurn(Opponent);
  test_board1.Play(0, 7);

  test_board2.ForceCardOnBoard(Ally, 0, 0, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 1, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 2, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 3, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 4, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 5, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 6, Ally);
  test_board2.ForceCardOnBoard(Opponent, 1, 8, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 7, Opponent);
  EXPECT_EQ(test_board1, test_board2);
  EXPECT_EQ(test_board1.GetWinner(), Opponent);
}

TEST(PlayTest, CASE7_Elemental){
  enum CardID ally_card_list[5]{BloodSoul, TRexaur, Anacondaur, Tonberry, Trauma};
  enum CardID opponent_card_list[5]{TonberryKing, Malboro, Ochu, Jelleye, Gerogero};

  enum Player turn = Ally;
  Rules rule(true, false, false, false, true, false, true); // Plus and Elemental
  enum Element elem_list[9]{None, None, Poison, None, None, None, None, None, None};
  Board test_board1(ally_card_list, opponent_card_list, rule, turn, elem_list);
  Board test_board2(ally_card_list, opponent_card_list, rule, turn);
  test_board2.SetElement(Poison, 2);
  
  test_board1.ForceCardOnBoard(Ally, 0, 0, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 1, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 2, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 3, Ally);
  test_board1.ForceCardOnBoard(Ally, 0, 4, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 5, Ally);
  test_board1.ForceCardOnBoard(Opponent, 0, 6, Ally);
  test_board1.ForceCardOnBoard(Opponent, 1, 8, Ally);
  test_board1.SetTurn(Opponent);
  test_board1.Play(0, 7);

  test_board2.ForceCardOnBoard(Ally, 0, 0, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 1, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 2, Ally);
  test_board2.ForceCardOnBoard(Ally, 0, 3, Opponent);
  test_board2.ForceCardOnBoard(Ally, 0, 4, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 5, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 6, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 1, 8, Opponent);
  test_board2.ForceCardOnBoard(Opponent, 0, 7, Opponent);
  EXPECT_EQ(test_board1, test_board2);
  EXPECT_EQ(test_board1.GetWinner(), Opponent);
}
