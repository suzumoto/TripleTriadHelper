#include <iostream>
#include <Rules.hpp>
#include <Board.hpp>
#include <CardData.hpp>

int main(int argc, char* argv[]){
  CardData data;
  enum CardID id = NullCard;

  for(int i = 0; i < 110; ++i){
    std::cout << i << std::endl;
    std::cout << data[++id] << std::endl;
  }

  return 0;
}
