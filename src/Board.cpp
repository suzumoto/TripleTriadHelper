#include <Board.hpp>

Board::Board(enum CardID ally_card_list_[5], enum CardID opponent_card_list_[5], Rules rules_, enum Player turn_):
  rules(rules_),
  turn(turn_),
  sente(turn_),
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
  for(int i = 0; i < num_total_cards; ++i){
    ally_card_list.push_back(ally_card_list_[i]);
    opponent_card_list.push_back(opponent_card_list_[i]);
  }
}

Board::Board(enum CardID ally_card_list_[5], enum CardID opponent_card_list_[5], Rules rules_, enum Player turn_, enum Element element_list_[9]):
  rules(rules_),
  turn(turn_),
  sente(turn_),
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
  for(int i = 0; i < num_total_cards; ++i){
    ally_card_list.push_back(ally_card_list_[i]);
    opponent_card_list.push_back(opponent_card_list_[i]);
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
    if(sente == Ally){
      if(num_ally_cards > 5) return Ally;
      else if(num_ally_cards == 5) return Unoccupied;
      else return Opponent;
    }
    else{
      if(num_opponent_cards > 5) return Opponent;
      else if(num_opponent_cards == 5) return Unoccupied;
      else return Ally;
    }
  }
  else{
    return Unoccupied;
  }
}

Card& Board::GetCard(int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in GetCard(int)\n");
#endif
  return card_data[card_list[position]];
}

void Board::SetTurn(enum Player player){
  turn = player;
}

void Board::Play(int index, int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in Play(int, int)\n");
  if(turn == Ally){
    if(index < 0 or ally_card_list.size() <= index) throw std::runtime_error("card index out of range in Play(int, int)\n");
  }
  else{
    if(index < 0 or opponent_card_list.size() <= index) throw std::runtime_error("card index out of range in Play(int, int)\n");
  }
  if(IsOccupied(position)) throw std::runtime_error("The place is already occupied. Play(int, int)\n");
  if(IsGameEnd()) throw std::runtime_error("The game is end. Play(int, int)\n");
#endif

  enum CardID card_id;
  if(turn == Ally) card_id = ally_card_list[index];
  else card_id = opponent_card_list[index];

#ifndef NDEBUG
  if(card_id == NullCard) throw std::runtime_error("Null card played in Play(int, int)\n");
#endif
  
  Card& card = card_data[card_id];

  bool special_flip = false;
  if(IsEnableSame()){
  }
  if(IsEnablePlus()){
  }
  if(IsEnableWallSame()){
  }
  if(!special_flip) NormalFlip(card, position);
  if(turn == Ally) ++num_ally_cards;
  else ++num_opponent_cards;
  --num_unoccupied_positions;
  if(num_unoccupied_positions == 0) is_game_end = true;
  card_list[position] = card_id;
  red_or_blue[position] = turn;

  if(turn == Ally){
    ally_card_list.erase(ally_card_list.begin() + index);
    turn = Opponent;
  }
  else{
    opponent_card_list.erase(opponent_card_list.begin() + index);
    turn = Ally;
  }
}

char int_to_char(int num){
  char char_num;
  if(num == 10) char_num = 'A';
  else char_num = '0' + num;
  return char_num;
}

std::ostream& operator<<(std::ostream& os, Board& board){
  if(board.IsGameEnd())
    os << " Turn: End " << std::endl;
  else if(board.turn == Ally)
    os << " Turn: You " << std::endl;
  else if(board.turn == Opponent)
    os << " Turn: Opp " << std::endl;
  
  if(!board.IsOccupied(0)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(0).GetUp()) << "  ";
  }
  if(!board.IsOccupied(1)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(1).GetUp()) << "  ";
  }
  if(!board.IsOccupied(2)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(2).GetUp()) << "  ";
  }
  os << std::endl;
  if(!board.IsOccupied(0)) os << "    ";
  else{
    os << int_to_char(board.GetCard(0).GetLeft())
       << (board.red_or_blue[0] == Ally ? '*' : ' ')
       << int_to_char(board.GetCard(0).GetRight())
       << " ";
  }
  if(!board.IsOccupied(1)) os << "    ";
  else{
    os << int_to_char(board.GetCard(1).GetLeft())
       << (board.red_or_blue[1] == Ally ? '*' : ' ')
       << int_to_char(board.GetCard(1).GetRight())
       << " ";
  }
  if(!board.IsOccupied(2)) os << "    ";
  else{
    os << int_to_char(board.GetCard(2).GetLeft())
       << (board.red_or_blue[2] == Ally ? '*' : ' ')
       << int_to_char(board.GetCard(2).GetRight())
       << " ";
  }
  os << std::endl;
  if(!board.IsOccupied(0)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(0).GetDown()) << "  ";
  }
  if(!board.IsOccupied(1)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(1).GetDown()) << "  ";
  }
  if(!board.IsOccupied(2)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(2).GetDown()) << "  ";
  }
  os << std::endl << std::endl;
  if(!board.IsOccupied(3)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(3).GetUp()) << "  ";
  }
  if(!board.IsOccupied(4)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(4).GetUp()) << "  ";
  }
  if(!board.IsOccupied(5)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(5).GetUp()) << "  ";
  }
  os << std::endl;
  if(!board.IsOccupied(3)) os << "    ";
  else{
    os << int_to_char(board.GetCard(3).GetLeft())
       << (board.red_or_blue[3] == Ally ? '*' : ' ')
       << int_to_char(board.GetCard(3).GetRight())
       << " ";
  }
  if(!board.IsOccupied(4)) os << "    ";
  else{
    os << int_to_char(board.GetCard(4).GetLeft())
       << (board.red_or_blue[4] == Ally ? '*' : ' ')
       << int_to_char(board.GetCard(4).GetRight())
       << " ";
  }
  if(!board.IsOccupied(5)) os << "    ";
  else{
    os << int_to_char(board.GetCard(5).GetLeft())
       << (board.red_or_blue[5] == Ally ? '*' : ' ')
       << int_to_char(board.GetCard(5).GetRight())
       << " ";
  }
  os << std::endl;
  if(!board.IsOccupied(3)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(3).GetDown()) << "  ";
  }
  if(!board.IsOccupied(4)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(4).GetDown()) << "  ";
  }
  if(!board.IsOccupied(5)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(5).GetDown()) << "  ";
  }
  os << std::endl << std::endl;

  if(!board.IsOccupied(6)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(6).GetUp()) << "  ";
  }
  if(!board.IsOccupied(7)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(7).GetUp()) << "  ";
  }
  if(!board.IsOccupied(8)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(8).GetUp()) << "  ";
  }
  os << std::endl;
  if(!board.IsOccupied(6)) os << "    ";
  else{
    os << int_to_char(board.GetCard(6).GetLeft())
       << (board.red_or_blue[6] == Ally ? '*' : ' ')
       << int_to_char(board.GetCard(6).GetRight())
       << " ";
  }
  if(!board.IsOccupied(7)) os << "    ";
  else{
    os << int_to_char(board.GetCard(7).GetLeft())
       << (board.red_or_blue[7] == Ally ? '*' : ' ')
       << int_to_char(board.GetCard(7).GetRight())
       << " ";
  }
  if(!board.IsOccupied(8)) os << "    ";
  else{
    os << int_to_char(board.GetCard(8).GetLeft())
       << (board.red_or_blue[8] == Ally ? '*' : ' ')
       << int_to_char(board.GetCard(8).GetRight())
       << " ";
  }
  os << std::endl;
  if(!board.IsOccupied(6)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(6).GetDown()) << "  ";
  }
  if(!board.IsOccupied(7)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(7).GetDown()) << "  ";
  }
  if(!board.IsOccupied(8)) os << "    ";
  else{
    os << " " << int_to_char(board.GetCard(8).GetDown()) << "  ";
  }
  
  return os << std::endl;
}

bool Board::IsEnableSame(){
  return rules.IsEnableSame();
}

bool Board::IsEnablePlus(){
  return rules.IsEnablePlus();
}

bool Board::IsEnableWallSame(){
  return rules.IsEnableWallSame();
}

bool Board::IsEnableElemental(){
  return rules.IsEnableElemental();
}

int Board::CorElement(Card& card, int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in CorElement(card&, int)\n");
#endif
  if(!IsEnableElemental()) return 0;
  if(GetElement(position) == None) return 0;
  if(card.GetElement() == None) return 0;
  if(GetElement(position) == card.GetElement()) return 1;
  return -1;
}

bool Board::IsUpFlip(Card& card, int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in IsUpFlip(Card&, int)\n");
#endif
  if(position <= 2) return false;

  int up_position = position - 3;
  if(!IsOccupied(up_position)) return false;
  if(red_or_blue[up_position] == turn) return false;

  Card& up_card = GetCard(up_position);
  int up_element_mod = CorElement(up_card, up_position);
  int this_element_mod = CorElement(card, position);
  
  if(up_card.GetDown() + up_element_mod < card.GetUp() + this_element_mod) return true;
  return false;
}

bool Board::IsDownFlip(Card& card, int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in IsDownFlip(Card&, int)\n");
#endif
  if(position >= 6) return false;

  int down_position = position + 3;
  if(!IsOccupied(down_position)) return false;
  if(red_or_blue[down_position] == turn) return false;
 
  Card& down_card = GetCard(down_position);
  int down_element_mod = CorElement(down_card, down_position);
  int this_element_mod = CorElement(card, position);

  if(down_card.GetUp() + down_element_mod < card.GetDown() + this_element_mod) return true;
  return false;
}

bool Board::IsLeftFlip(Card& card, int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in IsLeftFlip(Card&, int)\n");
#endif
  if(position % 3 == 0) return false;

  int left_position = position - 1;
  if(!IsOccupied(left_position)) return false;
  if(red_or_blue[left_position] == turn) return false;
  
  Card& left_card = GetCard(left_position);
  int left_element_mod = CorElement(left_card, left_position);
  int this_element_mod = CorElement(card, position);

  if(left_card.GetRight() + left_element_mod < card.GetLeft() + this_element_mod) return true;
  return false;
}


bool Board::IsRightFlip(Card& card, int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in IsRightFlip(Card&, int)\n");
#endif
  if(position % 3 == 2) return false;

  int right_position = position + 1;
  if(!IsOccupied(right_position)) return false;
  if(red_or_blue[right_position] == turn) return false;
  
  Card& right_card = GetCard(right_position);
  int right_element_mod = CorElement(right_card, right_position);
  int this_element_mod = CorElement(card, position);

  if(right_card.GetLeft() + right_element_mod < card.GetRight() + this_element_mod) return true;
  return false;
}

void Board::UpFlip(int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in UpFlip(int)\n");
#endif
  int up_position = position - 3;

#ifndef NDEBUG
  if(up_position < 0 or 9 < up_position) throw std::runtime_error("position out of range in UpFlip(int)\n");
  if(red_or_blue[up_position] == turn) throw std::runtime_error("Board information conflict in UpFlip(int)");
#endif
  red_or_blue[up_position] = turn;
  if(turn == Ally){
    --num_opponent_cards;
    ++num_ally_cards;
  }
  else{
    --num_ally_cards;
    ++num_opponent_cards;
  }
}

void Board::DownFlip(int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in DownFlip(int)\n");
#endif
  int down_position = position + 3;

#ifndef NDEBUG
  if(down_position < 0 or 9 < down_position) throw std::runtime_error("position out of range in DownFlip(int)\n");
  if(red_or_blue[down_position] == turn) throw std::runtime_error("Board information conflict in DownFlip(int)");
#endif
  red_or_blue[down_position] = turn;
  if(turn == Ally){
    --num_opponent_cards;
    ++num_ally_cards;
  }
  else{
    --num_ally_cards;
    ++num_opponent_cards;
  }
}

void Board::RightFlip(int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in RightFlip(int)\n");
#endif
  int right_position = position + 1;

#ifndef NDEBUG
  if(right_position < 0 or 9 < right_position) throw std::runtime_error("position out of range in RightFlip(int)\n");
  if(right_position % 3 == 0) throw std::runtime_error("position out of range in RightFlip(int)\n");
  if(red_or_blue[right_position] == turn) throw std::runtime_error("Board information conflict in RightFlip(int)");
#endif
  red_or_blue[right_position] = turn;
  if(turn == Ally){
    --num_opponent_cards;
    ++num_ally_cards;
  }
  else{
    --num_ally_cards;
    ++num_opponent_cards;
  }
}

void Board::LeftFlip(int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in LeftFlip(int)\n");
#endif
  int left_position = position - 1;

#ifndef NDEBUG
  if(left_position < 0 or 9 < left_position) throw std::runtime_error("position out of range in LeftFlip(int)\n");
  if(left_position % 3 == 2) throw std::runtime_error("position out of range in LeftFlip(int)\n");
  if(red_or_blue[left_position] == turn) throw std::runtime_error("Board information conflict in LeftFlip(int)");
#endif
  red_or_blue[left_position] = turn;
  if(turn == Ally){
    --num_opponent_cards;
    ++num_ally_cards;
  }
  else{
    --num_ally_cards;
    ++num_opponent_cards;
  }
}

void Board::NormalFlip(Card& card, int position){
#ifndef NDEBUG
  if(position < 0 or 9 < position) throw std::runtime_error("position out of range in NormalFlip(Card&, int)\n");
#endif
  if(IsUpFlip(card, position)) UpFlip(position);
  if(IsDownFlip(card, position)) DownFlip(position);
  if(IsRightFlip(card, position)) RightFlip(position);
  if(IsLeftFlip(card, position)) LeftFlip(position);
}
