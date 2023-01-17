#include <iostream>
#include <Rules.hpp>
#include <Board.hpp>
#include <CardData.hpp>

#include <chrono>

int main(int argc, char* argv[]){
  Rules only_open(true, false, false, false, false, false, false);
  enum CardID ally_card_list[5]{Geezard, Funguar, BiteBug, RedBat, Blobra};
  enum CardID opponent_card_list[5]{Gayla, Rinoa, FastitocalonF, Edea, Squall};
  Player sente = Ally;

  Board game_manager(ally_card_list, opponent_card_list, only_open, sente);


  auto start = std::chrono::high_resolution_clock::now();
  for(int i = 0; i < 9; ++i){
    game_manager.Play(0,i);
  }
  auto end = std::chrono::high_resolution_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  std::cout << elapsed << " msec." << std::endl;
  return 0;
}
