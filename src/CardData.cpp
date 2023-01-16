#include <CardData.hpp>

CardID& operator++(CardID& id){
  if(id == Squall){
    id = NullCard;
    return id;
  }
  if(id == NullCard){
    id = Geezard;
    return id;
  }
  int index = (int)id;
  if(index % 100 == 11) index += 90;
  else index++;
  id = (CardID)index;
  return id;
}

Card::Card(){
  id = NullCard;
  element = None;
  up = 0;
  down = 0;
  left = 0;
  right = 0;
}

Card::Card(enum CardID id_, int up_, int right_, int down_, int left_, enum Element element_){
  id = id_;
  element = element_;
  up = up_;
  right = right_;
  down = down_;
  left = left_;
}

std::ostream& operator<<(std::ostream& os, Card& card){
  os << card.id << " "
     << card.element << " "
     << card.up << " "
     << card.down << " "
     << card.left << " "
     << card.right << std::endl;
  return os;
}

CardData::CardData(){
  enum CardID id_iterator = NullCard;
  int list_iterator = 0;
  card_list[list_iterator++] = Card(++id_iterator,1,4,1,5,None);
  card_list[list_iterator++] = Card(++id_iterator,5,1,1,3,None);
  card_list[list_iterator++] = Card(++id_iterator,1,3,3,5,None);
  card_list[list_iterator++] = Card(++id_iterator,6,1,1,2,None);
  card_list[list_iterator++] = Card(++id_iterator,2,3,1,5,None);
  card_list[list_iterator++] = Card(++id_iterator,2,1,4,4,Thunder);
  card_list[list_iterator++] = Card(++id_iterator,1,5,4,1,None);
  card_list[list_iterator++] = Card(++id_iterator,3,5,2,1,Ground);
  card_list[list_iterator++] = Card(++id_iterator,2,1,6,1,None);
  card_list[list_iterator++] = Card(++id_iterator,4,2,4,3,None);
  card_list[list_iterator++] = Card(++id_iterator,2,1,2,6,Thunder);
  card_list[list_iterator++] = Card(++id_iterator,7,1,3,1,None);
  card_list[list_iterator++] = Card(++id_iterator,6,2,2,3,None);
  card_list[list_iterator++] = Card(++id_iterator,5,3,3,4,None);
  card_list[list_iterator++] = Card(++id_iterator,6,1,4,3,Cold);
  card_list[list_iterator++] = Card(++id_iterator,3,4,5,3,None);
  card_list[list_iterator++] = Card(++id_iterator,5,3,2,5,Wind);
  card_list[list_iterator++] = Card(++id_iterator,5,1,3,5,Poison);
  card_list[list_iterator++] = Card(++id_iterator,5,2,5,2,Thunder);
  card_list[list_iterator++] = Card(++id_iterator,4,4,5,2,Thunder);
  card_list[list_iterator++] = Card(++id_iterator,3,2,1,7,None);
  card_list[list_iterator++] = Card(++id_iterator,5,2,5,3,None);
  card_list[list_iterator++] = Card(++id_iterator,6,6,3,2,None);
  card_list[list_iterator++] = Card(++id_iterator,6,6,3,1,Ground);
  card_list[list_iterator++] = Card(++id_iterator,3,5,5,5,Poison);
  card_list[list_iterator++] = Card(++id_iterator,7,5,1,3,Ground);
  card_list[list_iterator++] = Card(++id_iterator,7,1,5,3,Cold);
  card_list[list_iterator++] = Card(++id_iterator,5,6,3,3,None);
  card_list[list_iterator++] = Card(++id_iterator,5,6,2,4,Fire);
  card_list[list_iterator++] = Card(++id_iterator,4,4,7,2,Fire);
  card_list[list_iterator++] = Card(++id_iterator,6,2,6,3,None);
  card_list[list_iterator++] = Card(++id_iterator,3,6,4,4,None);
  card_list[list_iterator++] = Card(++id_iterator,7,2,3,5,Ground);
  card_list[list_iterator++] = Card(++id_iterator,2,3,6,7,None);
  card_list[list_iterator++] = Card(++id_iterator,6,5,4,5,None);
  card_list[list_iterator++] = Card(++id_iterator,4,6,2,7,None);
  card_list[list_iterator++] = Card(++id_iterator,2,7,6,3,Fire);
  card_list[list_iterator++] = Card(++id_iterator,1,6,4,7,Thunder);
  card_list[list_iterator++] = Card(++id_iterator,7,3,1,6,None);
  card_list[list_iterator++] = Card(++id_iterator,7,4,4,4,None);
  card_list[list_iterator++] = Card(++id_iterator,3,7,3,6,None);
  card_list[list_iterator++] = Card(++id_iterator,6,2,7,3,Poison);
  card_list[list_iterator++] = Card(++id_iterator,4,5,5,6,Ground);
  card_list[list_iterator++] = Card(++id_iterator,7,5,4,3,Fire);
  card_list[list_iterator++] = Card(++id_iterator,6,5,6,5,None);
  card_list[list_iterator++] = Card(++id_iterator,3,6,5,7,None);
  card_list[list_iterator++] = Card(++id_iterator,7,6,5,3,Water);
  card_list[list_iterator++] = Card(++id_iterator,3,10,2,1,None);
  card_list[list_iterator++] = Card(++id_iterator,6,2,6,7,None);
  card_list[list_iterator++] = Card(++id_iterator,5,5,7,4,None);
  card_list[list_iterator++] = Card(++id_iterator,7,7,4,2,Poison);
  card_list[list_iterator++] = Card(++id_iterator,7,2,7,4,Fire);
  card_list[list_iterator++] = Card(++id_iterator,5,3,7,6,None);
  card_list[list_iterator++] = Card(++id_iterator,4,6,7,4,None);
  card_list[list_iterator++] = Card(++id_iterator,6,6,2,7,None);
  card_list[list_iterator++] = Card(++id_iterator,2,8,8,4,None);
  card_list[list_iterator++] = Card(++id_iterator,7,8,3,4,Wind);
  card_list[list_iterator++] = Card(++id_iterator,4,8,7,3,None);
  card_list[list_iterator++] = Card(++id_iterator,7,2,8,5,None);
  card_list[list_iterator++] = Card(++id_iterator,1,8,8,3,Poison);
  card_list[list_iterator++] = Card(++id_iterator,8,2,8,2,None);
  card_list[list_iterator++] = Card(++id_iterator,6,8,4,5,None);
  card_list[list_iterator++] = Card(++id_iterator,4,8,5,6,None);
  card_list[list_iterator++] = Card(++id_iterator,1,8,4,8,None);
  card_list[list_iterator++] = Card(++id_iterator,6,5,8,4,None);
  card_list[list_iterator++] = Card(++id_iterator,7,5,8,1,None);
  card_list[list_iterator++] = Card(++id_iterator,8,4,4,8,None);
  card_list[list_iterator++] = Card(++id_iterator,8,8,4,4,None);
  card_list[list_iterator++] = Card(++id_iterator,8,5,2,8,Thunder);
  card_list[list_iterator++] = Card(++id_iterator,5,6,6,8,None);
  card_list[list_iterator++] = Card(++id_iterator,8,6,7,3,None);
  card_list[list_iterator++] = Card(++id_iterator,8,3,5,8,None);
  card_list[list_iterator++] = Card(++id_iterator,8,8,5,4,None);
  card_list[list_iterator++] = Card(++id_iterator,5,7,8,5,None);
  card_list[list_iterator++] = Card(++id_iterator,6,8,4,7,None);
  card_list[list_iterator++] = Card(++id_iterator,1,8,7,7,None);
  card_list[list_iterator++] = Card(++id_iterator,7,7,2,8,None);
  card_list[list_iterator++] = Card(++id_iterator,4,4,8,9,None);
  card_list[list_iterator++] = Card(++id_iterator,9,6,7,3,None);
  card_list[list_iterator++] = Card(++id_iterator,3,7,9,6,None);
  card_list[list_iterator++] = Card(++id_iterator,9,3,9,2,None);
  card_list[list_iterator++] = Card(++id_iterator,9,4,8,4,None);
  card_list[list_iterator++] = Card(++id_iterator,2,9,9,4,Thunder);
  card_list[list_iterator++] = Card(++id_iterator,6,7,4,9,Cold);
  card_list[list_iterator++] = Card(++id_iterator,9,6,2,8,Fire);
  card_list[list_iterator++] = Card(++id_iterator,8,9,6,2,None);
  card_list[list_iterator++] = Card(++id_iterator,5,1,9,9,Ground);
  card_list[list_iterator++] = Card(++id_iterator,9,5,2,9,Ground);
  card_list[list_iterator++] = Card(++id_iterator,8,4,10,4,None);
  card_list[list_iterator++] = Card(++id_iterator,5,10,8,3,None);
  card_list[list_iterator++] = Card(++id_iterator,7,10,1,7,Water);
  card_list[list_iterator++] = Card(++id_iterator,8,10,3,5,None);
  card_list[list_iterator++] = Card(++id_iterator,10,1,7,7,None);
  card_list[list_iterator++] = Card(++id_iterator,7,4,6,10,None);
  card_list[list_iterator++] = Card(++id_iterator,9,10,4,2,Holy);
  card_list[list_iterator++] = Card(++id_iterator,7,2,7,10,Fire);
  card_list[list_iterator++] = Card(++id_iterator,10,8,2,6,None);
  card_list[list_iterator++] = Card(++id_iterator,3,1,10,10,Poison);
  card_list[list_iterator++] = Card(++id_iterator,4,4,9,10,None);
  card_list[list_iterator++] = Card(++id_iterator,10,7,2,8,None);
  card_list[list_iterator++] = Card(++id_iterator,6,7,6,10,None);
  card_list[list_iterator++] = Card(++id_iterator,5,10,3,9,None);
  card_list[list_iterator++] = Card(++id_iterator,10,8,6,4,None);
  card_list[list_iterator++] = Card(++id_iterator,9,6,10,2,None);
  card_list[list_iterator++] = Card(++id_iterator,2,6,9,10,None);
  card_list[list_iterator++] = Card(++id_iterator,8,5,10,6,None);
  card_list[list_iterator++] = Card(++id_iterator,4,10,2,10,None);
  card_list[list_iterator++] = Card(++id_iterator,10,10,3,3,None);
  card_list[list_iterator++] = Card(++id_iterator,6,9,10,4,None);
  card_list[list_iterator++] = Card(++id_iterator,10,4,6,9,None);
}

Card& CardData::operator[](const enum CardID& id){
  int index = (int)id;
  int r = index % 100;
  int q = index / 100;
  if(r <= 0 or r >= 12) throw std::runtime_error("rem out of range\n");
  if(q <= -1 or q >= 11) throw std::runtime_error("quo out of range\n");
  index = (q-1) * 11 + r - 1;
  return card_list[index];
}
