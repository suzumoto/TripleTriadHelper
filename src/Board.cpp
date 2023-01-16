#include <Board.hpp>

Board::Board(Rules rules_, enum Player turn_):
  rules(rules_),
  turn(turn_),
  num_opponent_cards(0),
  num_ally_cards(0),
  num_unoccupied_positions(9),
  is_game_end(false)
{
  for(int i = 0; i < num_positions; ++i){
    element_list[i] = None;
    red_or_blue[i] = Unoccupied;
    card_list[i] = NullCard;
  }
}

Board::Board(Rules rules_, enum Player turn_, enum Element element_list_[9]):
  rules(rules_),
  turn(turn_),
  num_opponent_cards(0),
  num_ally_cards(0),
  num_unoccupied_positions(9),
  is_game_end(false)
{
  for(int i = 0; i < num_positions; ++i){
    element_list[i] = element_list_[i];
    red_or_blue[i] = Unoccupied;
    card_list[i] = NullCard;
  }
}

void Board::SetElement(enum Element el, int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range\n");
#endif
  element_list[position] = el;
}

enum Element Board::GetElement(int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range\n");
#endif
  return element_list[position];
}

bool Board::IsOccupied(int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range\n");
  if(red_or_blue[position] != Unoccupied and card_list[position] == NullCard) throw std::runtime_error("card information conflicted\n");
  if(red_or_blue[position] == Unoccupied and card_list[position] != NullCard) throw std::runtime_error("card information conflicted\n");
#endif
  return (red_or_blue[position] != Unoccupied);
}

bool Board::IsGameEnd(){
  return is_game_end;
}

enum Player Board::GetTurnPlayer(){
#ifndef NDEBUG
  if(turn == Unoccupied) throw std::runtime_error("turn unoccupied\n");
#endif
  return turn;
}

enum Player Board::GetWinner(){
  if(is_game_end){
#ifndef NDEBUG
    if(num_opponent_cards + num_ally_cards != num_positions) throw std::runtime_error("the sum of the number of the cards is not 9 while game is end.\n");
    if(num_unoccupied_positions != 0) throw std::runtime_error("Unoccupied positions still remain while game is end\n");
#endif
    if(num_opponent_cards < num_ally_cards) return Ally;
    else if(num_ally_cards < num_opponent_cards) return Opponent;
    else return Unoccupied;
  }
  else return Unoccupied;
}

void Board::SetTurn(enum Player player){
  turn = player;
}

void Board::Play(enum CardID card, int position){
  
}
