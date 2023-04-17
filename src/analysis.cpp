#include <Board.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <omp.h>

int main(int argc, char* argv[]){
  const CardData card_data;
  
  // Open; Level N vs Level N
#pragma omp parallel for
  for(int level = 1; level <= 10; ++level){
    std::vector<enum CardID> level_list;
    Rules rule(true, false, false, false, false, false, false); // Open
    for(int i = 0; i < 11; ++i){
      level_list.push_back((CardID)(level*100 + i + 1));
    }
    std::string filename = "level" + std::to_string(level) + "_analysis.txt";
    std::ofstream ofs(filename);
    enum CardID ally_card_list[5];
    enum CardID opponent_card_list[5];
    for(int a1 = 0; a1 < 7; ++a1){
      for(int a2 = a1 + 1; a2 < 8; ++a2){
	for(int a3 = a2 + 1; a3 < 9; ++a3){
	  for(int a4 = a3 + 1; a4 < 10; ++a4){
	    for(int a5 = a4 + 1; a5 < 11; ++a5){
	      ally_card_list[0] = level_list[a1];
	      ally_card_list[1] = level_list[a2];
	      ally_card_list[2] = level_list[a3];
	      ally_card_list[3] = level_list[a4];
	      ally_card_list[4] = level_list[a5];

	      std::vector<enum CardID> reminder(level_list);
	      reminder.erase(reminder.begin() + a5);
	      reminder.erase(reminder.begin() + a4);
	      reminder.erase(reminder.begin() + a3);
	      reminder.erase(reminder.begin() + a2);
	      reminder.erase(reminder.begin() + a1);
	      for(int bn = 0; bn < 6; ++bn){
		std::vector<enum CardID> op_hand(reminder);
		op_hand.erase(op_hand.begin() + bn);
		opponent_card_list[0] = op_hand[0];
		opponent_card_list[1] = op_hand[1];
		opponent_card_list[2] = op_hand[2];
		opponent_card_list[3] = op_hand[3];
		opponent_card_list[4] = op_hand[4];

		std::unordered_map<long, int> work_a;
		Board game_a(ally_card_list, opponent_card_list, rule, Ally, card_data);
		int eval_a;
		game_a.BestSearch(work_a, eval_a);
		
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
		if(eval_a == 1)
		  ofs << "Black Win" << std::endl;
		else if(eval_a == 0)
		  ofs << "Draw" << std::endl;
		else ofs << "White Win" << std::endl;
	      }
	    }
	  }
	}
      }
    }
  }
  
  return 0;
}
