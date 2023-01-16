#pragma once
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
  
public:
  Board(Rules, enum Player turn);
  Board(Rules, enum Player turn, enum Element element_list[9]);
  ~Board(){};
  void SetElement(enum Element el, int position);
  enum Element GetElement(int position);
  bool IsOccupied(int position);
  bool IsGameEnd();
  enum Player GetTurnPlayer();
  enum Player GetWinner();
  void SetTurn(enum Player player);
  void Play(enum CardID card, int position);
};

