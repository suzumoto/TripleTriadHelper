#include <iostream>
#include <Rules.hpp>
#include <Board.hpp>
#include <CardData.hpp>

int main(int argc, char* argv[]){
  Rules only_open(true, false, false, false, false, false, false);
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum CardID opponent_card_list[5]{Gayla, Gesper, FastitocalonF, BloodSoul};
  Player sente = Ally;

  Board game_manager(ally_card_list, opponent_card_list, only_open, sente);
  
  for(int i = 0; i < 9; ++i){
    std::cout << game_manager << std::endl;
    game_manager.Play(0,i);
  }
  std::cout << game_manager << std::endl;
  return 0;
}
