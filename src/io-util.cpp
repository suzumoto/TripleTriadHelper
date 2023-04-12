#include <io-util.hpp>
#include <CardData.hpp>
#include <string>

io_util::io_util(){
  enum CardID id_iterator = Geezard;
  CardData data;
  while(id_iterator != NullCard){
    std::string num;
    const Card& card = data[id_iterator];
    int up = card.GetUp();
    int left = card.GetLeft();
    int down = card.GetDown();
    int right = card.GetRight();
    num += ((up == 10)?"a":std::to_string(up))
      + ((right == 10)?"a":std::to_string(right))
      + ((down == 10)?"a":std::to_string(down))
      + ((left == 10)?"a":std::to_string(left));
    cardnum_to_id.insert(std::make_pair(num, id_iterator));
    ++id_iterator;
  }
}

io_util::~io_util(){
}
