#include <iostream>
#include <chrono>
#include <Board.hpp>
#include <CardData.hpp>
#include <Rules.hpp>
#include <io-util.hpp>

int main(int argc, char* argv[]){
  enum CardID ally_card_list[5]{NullCard, NullCard, NullCard, NullCard, NullCard};
  enum CardID opponent_card_list[5]{NullCard, NullCard, NullCard, NullCard, NullCard};
  io_util util;
  CardData card_data;
  std::unordered_map<long, int> already_searched_list;
  for(int i = 0; i < 5; ++i){
    std::cout << "Input Ally CardID #" << i+1 << std::endl;
    std::string input;
    std::cin >> input;
    if(util.cardnum_to_id.find(input) == util.cardnum_to_id.end()){
      std::cout << "Wrong Input." << std::endl;
      --i;
      continue;
    }	      
    CardID id = util.cardnum_to_id[input];
    if(id == NullCard){
      std::cout << "Wrong Input." << std::endl;
      --i;
      continue;
    }
    ally_card_list[i] = int_to_cardID(id);
  }
  for(int i = 0; i < 5; ++i){
    std::cout << "Input Opponent CardID #" << i+1 << std::endl;
    std::string input;
    std::cin >> input;
    if(util.cardnum_to_id.find(input) == util.cardnum_to_id.end()){
      std::cout << "Wrong Input." << std::endl;
      --i;
      continue;
    }
    CardID id = util.cardnum_to_id[input];
    if(id == NullCard){
      std::cout << "Wrong Input." << std::endl;
      --i;
      continue;
    }
    opponent_card_list[i] = int_to_cardID(id);
  }
  Rules rule(true, false, false, false, false, false, false);
  std::cout << "Rules: Open" << std::endl;
  enum Player sente;
  while(true){
    std::cout << "Which has the first move? 0/Ally, 1/Opponent" << std::endl;
    int int_sente;
    std::cin >> int_sente;
    if(int_sente != 0 and int_sente != 1){
      std::cout << "Wrong Input." << std::endl;
      continue;
    }
    if(int_sente == 0){
      sente = Ally;
    }
    else sente = Opponent;
    break;
  }
  Board gameboard(ally_card_list, opponent_card_list, rule, sente, card_data);
  while(!gameboard.IsGameEnd()){
    std::cout << gameboard << std::endl;
    std::cout << "input Move(index, position) or Search(9999)" << std::endl;
    int index, position;
    std::cin >> index;
    if(index == 9999){
      auto start = std::chrono::high_resolution_clock::now();
      std::pair<int, int> move = gameboard.BestSearch(already_searched_list);
      auto end = std::chrono::high_resolution_clock::now();
      double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
      std::cout << "time elapsed for search = " << elapsed << " m sec." << std::endl;
      if(move.first == -1){
	std::cout << "Lose " << std::endl;
	continue;
      }
      std::cout << "Best Move = (" << move.first << ", " << move.second << ")" << std::endl;
      gameboard.Play(move.first, move.second);
      continue;
    }
    int num_turn_playercard = ((gameboard.GetTurnPlayer() == Ally)?gameboard.GetAllyCardList().size():gameboard.GetOpponentCardList().size());
    if(index < 0 or num_turn_playercard <= index){
      std::cout << "Wrong Input" << std::endl;
      continue;
    }
    std::cin >> position;
    if(position < 0 or 8 < position){
      std::cout << "Wrong Input" << std::endl;
      continue;
    }
    gameboard.Play(index, position);
  }
  std::cout << gameboard << std::endl;
  return 0;
}
