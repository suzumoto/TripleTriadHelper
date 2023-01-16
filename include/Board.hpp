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
  void SetElement(enum Element el, int position);
  void GetElement(int position);
  bool IsOccupied(int position);
  bool IsGameEnd();
  enum Player GetTurnPlayer(int position);
  enum Player GetWinner();
  void SetTurn(enum Player first_player);
  void Play(enum CardID card, int position);
};

