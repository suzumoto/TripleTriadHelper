#pragma once
#include <vector>
#include <Rules.hpp>
#include <CardData.hpp>

enum Player{
  Unoccupied,
  Ally,
  Opponent
};

class Board{
private:
  CardData card_data;
  const int num_positions = 9;
  Rules rules;
  enum Element element_list[9];
  enum Player red_or_blue[9];
  enum CardID card_list[9];
  enum Player turn;
  int num_opponent_cards;
  int num_ally_cards;
  int num_unoccupied_positions;
  bool is_game_end;

  const int num_total_cards = 5;
  std::vector<enum CardID> ally_card_list;
  std::vector<enum CardID> opponent_card_list;
  
public:
  Board(enum CardID ally_card_list[5], enum CardID opponent_card_list[5], Rules, enum Player turn);
  Board(enum CardID ally_card_list[5], enum CardID opponent_card_list[5], Rules, enum Player turn, enum Element element_list[9]);
  ~Board(){};
  void SetElement(enum Element el, int position);
  enum Element GetElement(int position);
  bool IsOccupied(int position);
  bool IsGameEnd();
  enum Player GetTurnPlayer();
  enum Player GetWinner();
  Card& GetCard(int position);
  void SetTurn(enum Player player);
  void Play(int index, int position);
  friend std::ostream& operator<<(std::ostream& os, Board& board);
  
protected:
  bool IsEnableSame();
  bool IsEnablePlus();
  bool IsEnableWallSame();
  bool IsUpFlip(Card& card, int position);
  bool IsDownFlip(Card& card, int position);
  bool IsRightFlip(Card& card, int position);
  bool IsLeftFlip(Card& card, int position);
  void UpFlip(int position);
  void DownFlip(int position);
  void RightFlip(int position);
  void LeftFlip(int position);
  void NormalFlip(Card& card, int position);
};

