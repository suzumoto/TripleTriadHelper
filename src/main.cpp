#include <iostream>
#include <Board.hpp>
#include <CardData.hpp>
#include <Rules.hpp>

int main(int argc, char* argv[]){
  enum CardID ally_card_list[5]{NullCard, NullCard, NullCard, NullCard, NullCard};
  enum CardID opponent_card_list[5]{NullCard, NullCard, NullCard, NullCard, NullCard};
  for(int i = 0; i < 5; ++i){
    std::cout << "Input Ally CardID #" << i+1 << std::endl;
    int int_id;
    std::cin >> int_id;
    CardID id = int_to_cardID(int_id);
    if(id == NullCard){
      std::cout << "Wrong Input." << std::endl;
      --i;
      continue;
    }
    ally_card_list[i] = int_to_cardID(id);
  }
  for(int i = 0; i < 5; ++i){
    std::cout << "Input Opponent CardID #" << i+1 << std::endl;
    int int_id;
    std::cin >> int_id;
    CardID id = int_to_cardID(int_id);
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
  Board gameboard(ally_card_list, opponent_card_list, rule, sente);
  while(!gameboard.IsGameEnd()){
    std::cout << gameboard << std::endl;
    std::cout << "input Move(index, position) or Search(9999)" << std::endl;
    int index, position;
    std::cin >> index;
    if(index == 9999){
      std::pair<int, int> move = gameboard.BestSearch();
      if(move.first == -1)
	std::cout << "Possibly Lose" << std::endl;
      std::cout << "Best Move = (" << move.first << ", " << move.second << ")" << std::endl;
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
  return 0;
}
