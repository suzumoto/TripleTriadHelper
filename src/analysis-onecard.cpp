#include <Board.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <omp.h>

int main(int argc, char* argv[]){
  const CardData card_data;
  
  // Open Same Plus; Level N vs Level N
#pragma omp parallel for
  for(int level = 1; level <= 10; ++level){
    Rules rule(true, false, false, true, true, true, false); // Open
    std::string filename = "level" + std::to_string(level) + "_analysis-onecard.txt";
    std::ofstream ofs(filename);
    enum CardID ally_card_list[5];
    enum CardID opponent_card_list[5];
    for(int i = 0; i < 11; ++i){
      ally_card_list[0] = (CardID)(level*100 + i + 1);
      ally_card_list[1] = (CardID)(level*100 + i + 1);
      ally_card_list[2] = (CardID)(level*100 + i + 1);
      ally_card_list[3] = (CardID)(level*100 + i + 1);
      ally_card_list[4] = (CardID)(level*100 + i + 1);
      
      opponent_card_list[0] = (CardID)(level*100 + i + 1);
      opponent_card_list[1] = (CardID)(level*100 + i + 1);
      opponent_card_list[2] = (CardID)(level*100 + i + 1);
      opponent_card_list[3] = (CardID)(level*100 + i + 1);
      opponent_card_list[4] = (CardID)(level*100 + i + 1);
      std::unordered_map<long, int> work;
      Board game(ally_card_list, opponent_card_list, rule, Ally, card_data);
      int eval;
      game.BestSearch(work, eval);
		
      ofs << "Black, " << ally_card_list[0]
	  << ", " << ally_card_list[1]
	  << ", " << ally_card_list[2]
	  << ", " << ally_card_list[3]
	  << ", " << ally_card_list[4]
	  << ", White, " << opponent_card_list[0]
	  << ", " << opponent_card_list[1]
	  << ", " << opponent_card_list[2]
	  << ", " << opponent_card_list[3]
	  << ", " << opponent_card_list[4]
	  << ", ";
      if(eval == 1)
	ofs << "Black Win" << std::endl;
      else if(eval == 0)
	ofs << "Draw" << std::endl;
      else ofs << "White Win" << std::endl;
    }
  }
  
  return 0;
}
