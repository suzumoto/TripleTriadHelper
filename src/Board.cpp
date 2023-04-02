#include <Board.hpp>
#include <string>

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

Board::Board(const Board& board):
  rules(board.rules),
  turn(board.turn),
  sente(board.turn),
  num_opponent_cards(board.num_opponent_cards),
  num_ally_cards(board.num_ally_cards),
  num_unoccupied_positions(board.num_unoccupied_positions),
  is_game_end(board.is_game_end),
  ally_card_list(board.ally_card_list),
  opponent_card_list(board.opponent_card_list)
{
  for(int i = 0; i < num_positions; ++i){
    element_list[i] = board.element_list[i];
    red_or_blue[i] = board.red_or_blue[i];
    card_list[i] = board.card_list[i];
  }
}

void Board::SetElement(enum Element el, int position){
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in SetElement");
#endif
  element_list[position] = el;
}

enum Element Board::GetElement(int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in GetElement");
#endif
  return element_list[position];
}

bool Board::IsOccupied(int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position){
    std::string msg("position out of range in IsOccupied, position = ");
    msg += std::to_string(position);
    throw std::runtime_error(msg);
  }
  if(red_or_blue[position] != Unoccupied and card_list[position] == NullCard) throw std::runtime_error("card information conflicted\n");
  if(red_or_blue[position] == Unoccupied and card_list[position] != NullCard) throw std::runtime_error("card information conflicted\n");
#endif
  return (red_or_blue[position] != Unoccupied);
}

bool Board::IsGameEnd() const{
  return is_game_end;
}

enum Player Board::GetTurnPlayer() const{
#ifndef NDEBUG
  if(turn == Unoccupied) throw std::runtime_error("turn unoccupied\n");
#endif
  return turn;
}

const std::vector<enum CardID>& Board::GetTurnPlayerCardList() const{
  if(GetTurnPlayer() == Ally)
    return ally_card_list;
  else return opponent_card_list;
}

enum Player Board::GetWinner() const{
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

const Card& Board::GetCard(int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in GetCard(int)\n");
#endif
  return card_data[card_list[position]];
}

void Board::SetTurn(enum Player player){
  turn = player;
}

void Board::Play(int index, int position){
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in Play(int, int)\n");
  if(turn == Ally){
    if(index < 0 or ally_card_list.size() <= index) throw std::runtime_error("card index out of range in Play(int, int)\n");
  }
  else{
    if(index < 0 or opponent_card_list.size() <= index) throw std::runtime_error("card index out of range in Play(int, int)\n");
  }
#ifndef NDEBUG
  try{
#endif
    if(IsOccupied(position)) throw std::runtime_error("The place is already occupied. Play(int, int)\n");
#ifndef NDEBUG
  }
  catch(std::runtime_error& e){
    std::cout << e.what() << std::endl;
    throw std::runtime_error("Unexpected Error in Play");
  }
#endif
  if(IsGameEnd()) throw std::runtime_error("The game is end. Play(int, int)\n");
#endif

  enum CardID card_id;
  if(turn == Ally) card_id = ally_card_list[index];
  else card_id = opponent_card_list[index];

#ifndef NDEBUG
  if(card_id == NullCard) throw std::runtime_error("Null card played in Play(int, int)\n");
#endif
  
  const Card& card = card_data[card_id];

  bool special_flip = false;
  if(IsEnableSame()){ // includes wall-same procedures
    int same_flag = SameFlag(card, position);
    special_flip = same_flag;
    CascadeWithFlag(position, same_flag);
  }
  if(IsEnablePlus()){
    int plus_flag = PlusFlag(card, position);
    special_flip = (special_flip and plus_flag);
    CascadeWithFlag(position, plus_flag);
  }
  if(!special_flip) NormalFlip(card, position);
  else{
    if(IsUpFlip(card, position)) CascadeFlip(position - 3);
    if(IsDownFlip(card, position)) CascadeFlip(position + 3);
    if(IsRightFlip(card, position)) CascadeFlip(position + 1);
    if(IsLeftFlip(card, position)) CascadeFlip(position - 1);
  }
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

void Board::ForceCardOnBoard(enum Player srcPlayer, int index, int position, enum Player dstPlayer){
#ifndef NDEBUG
  if(position < 0 or position > 8) throw std::runtime_error("Position out of range, in ForceCardOnBoard(Player, int, int, Player)");
  if(srcPlayer == Ally)
    if(index < 0 or ally_card_list.size() <= index) throw std::runtime_error("index out of range, in ForceCardOnBoard(Player, int, int, Player)");
  if(srcPlayer == Opponent)
    if(index < 0 or opponent_card_list.size() <= index) throw std::runtime_error("index out of range, in ForceCardOnBoard(Player, int, int, Player)");
  if(red_or_blue[position] != Unoccupied) throw std::runtime_error("Position already occupied, in ForceCardOnBoard(Player, int, int, Player)");
#endif
  red_or_blue[position] = dstPlayer;
  if(srcPlayer == Ally){
    card_list[position] = ally_card_list[index];
    ally_card_list.erase(ally_card_list.begin() + index);
  }
  if(srcPlayer == Opponent){
    card_list[position] = opponent_card_list[index];
    opponent_card_list.erase(opponent_card_list.begin() + index);
  }
  if(dstPlayer == Ally) ++num_ally_cards;
  if(dstPlayer == Opponent) ++num_opponent_cards;
  --num_unoccupied_positions;
  if(num_unoccupied_positions == 0) is_game_end = true;
}

int Board::MoveEval(int index, int position) const{
#ifndef NDEBUG
  if(IsGameEnd()) throw std::runtime_error("Do not call MoveEval on a final board");
#endif
  Board next_board(*this);
  next_board.Play(index, position);
  if(next_board.IsGameEnd()){
    if(next_board.GetWinner() == Unoccupied) return 0; // Draw
    if(next_board.GetWinner() == GetTurnPlayer()) return 1; // Win
    else return -1; // Lose
  }
  std::vector<int> empty_list;
#ifndef NDEBUG
  try{
#endif
    for(int i = 0; i < num_positions; ++i){
      if(!next_board.IsOccupied(i))
	empty_list.push_back(i);
    }
#ifndef NDEBUG
  }
  catch(std::runtime_error& e){
    std::cout << e.what() << std::endl;
    throw std::runtime_error("Unexpected Error in Move Eval(int, int)");
  }
#endif
  const std::vector<enum CardID>& hand_list = next_board.GetTurnPlayerCardList();
  int eval_sum = 0;
  for(int card_index = 0; card_index < hand_list.size(); ++card_index){
    for(int empty_position: empty_list){
      int eval = next_board.MoveEval(card_index, empty_position);
      if(eval == 1)
	return -1;
      eval_sum += eval;
    }
  }
  if(-eval_sum == hand_list.size() * empty_list.size())
    return 1;
  else return 0;
}

int Board::MoveEval(int index, int position, long& count) const{
  ++count;
#ifndef NDEBUG
  if(IsGameEnd()) throw std::runtime_error("Do not call MoveEval on a final board");
#endif
  Board next_board(*this);
  next_board.Play(index, position);
  if(next_board.IsGameEnd()){
    if(next_board.GetWinner() == Unoccupied) return 0; // Draw
    if(next_board.GetWinner() == GetTurnPlayer()) return 1; // Win
    else return -1; // Lose
  }
  std::vector<int> empty_list;
#ifndef NDEBUG
  try{
#endif
    for(int i = 0; i < num_positions; ++i){
      if(!next_board.IsOccupied(i))
	empty_list.push_back(i);
    }
#ifndef NDEBUG
  }
  catch(std::runtime_error& e){
    std::cerr << e.what() << std::endl;
    throw std::runtime_error("Unexpected Error in MoveEval(int, int long&)");
  }
#endif
  const std::vector<enum CardID>& hand_list = next_board.GetTurnPlayerCardList();
  int eval_sum = 0;
  for(int card_index = 0; card_index < hand_list.size(); ++card_index){
    for(int empty_position: empty_list){
      int eval = next_board.MoveEval(card_index, empty_position, count);
      if(eval == 1)
	return -1;
      eval_sum += eval;
    }
  }
  if(-eval_sum == hand_list.size() * empty_list.size())
    return 1;
  else return 0;
}

static char int_to_char(int num){
  char char_num;
  if(num == 10) char_num = 'A';
  else char_num = '0' + num;
  return char_num;
}

std::ostream& operator<<(std::ostream& os, const Board& board){
  os << std::endl;
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

bool operator==(const Board& rhs, const Board& lhs){
  if(rhs.rules != lhs.rules) return false;
  for(int i = 0; i < rhs.num_positions; ++i){
    if(rhs.element_list[i] != lhs.element_list[i]) return false;
    if(rhs.red_or_blue[i] != lhs.red_or_blue[i]) return false;
    if(rhs.card_list[i] != lhs.card_list[i]) return false;
  }
  if(rhs.turn != lhs.turn) return false;
  if(rhs.sente != lhs.sente) return false;
  if(rhs.num_opponent_cards != lhs.num_opponent_cards) return false;
  if(rhs.num_ally_cards != lhs.num_ally_cards) return false;
  if(rhs.num_unoccupied_positions != lhs.num_unoccupied_positions) return false;
  if(rhs.is_game_end != lhs.is_game_end) return false;
  if(rhs.ally_card_list.size() != lhs.ally_card_list.size()) return false;
  if(rhs.opponent_card_list.size() != lhs.opponent_card_list.size()) return false;
  for(int i = 0; i < rhs.ally_card_list.size(); ++i){
    if(rhs.ally_card_list[i] != lhs.ally_card_list[i]) return false;
  }
  for(int i = 0; i < rhs.opponent_card_list.size(); ++i){
    if(rhs.opponent_card_list[i] != lhs.opponent_card_list[i]) return false;
  }
  return true;
}

bool Board::IsEnableSame() const{
  return rules.IsEnableSame();
}

bool Board::IsEnablePlus() const{
  return rules.IsEnablePlus();
}

bool Board::IsEnableWallSame() const{
  return rules.IsEnableWallSame() and rules.IsEnableSame();
}

bool Board::IsEnableElemental() const{
  return rules.IsEnableElemental();
}

int Board::CorElement(const Card& card, int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in CorElement(card&, int)\n");
#endif
  if(!IsEnableElemental()) return 0;
  if(GetElement(position) == None) return 0;
  if(card.GetElement() == None) return 0;
  if(GetElement(position) == card.GetElement()) return 1;
  return -1;
}

bool Board::IsUpFlip(const Card& card, int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in IsUpFlip(Card&, int)\n");
#endif
  if(position <= 2) return false;

  int up_position = position - 3;
#ifndef NDEBUG
  try{
#endif
    if(!IsOccupied(up_position)) return false;
#ifndef NDEBUG
  }
  catch(std::runtime_error& e){
    std::cerr << e.what() << std::endl;
    throw std::runtime_error("Unexpected Error in IsUpflip");
  }
#endif
  if(red_or_blue[up_position] == turn) return false;

  const Card& up_card = GetCard(up_position);
  int up_element_mod = CorElement(up_card, up_position);
  int this_element_mod = CorElement(card, position);
  
  if(up_card.GetDown() + up_element_mod < card.GetUp() + this_element_mod) return true;
  return false;
}

bool Board::IsDownFlip(const Card& card, int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in IsDownFlip(Card&, int)\n");
#endif
  if(position >= 6) return false;

  int down_position = position + 3;
#ifndef NDEBUG
  try{
#endif
    if(!IsOccupied(down_position)) return false;
#ifndef NDEBUG
  }
  catch(std::runtime_error& e){
    std::cout << e.what() << std::endl;
    throw std::runtime_error("Unexpected error in Is Down Flip");
  }
#endif
  if(red_or_blue[down_position] == turn) return false;
 
  const Card& down_card = GetCard(down_position);
  int down_element_mod = CorElement(down_card, down_position);
  int this_element_mod = CorElement(card, position);

  if(down_card.GetUp() + down_element_mod < card.GetDown() + this_element_mod) return true;
  return false;
}

bool Board::IsLeftFlip(const Card& card, int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in IsLeftFlip(Card&, int)\n");
#endif
  if(position % 3 == 0) return false;

  int left_position = position - 1;
#ifndef NDEBUG
  try{
#endif
    if(!IsOccupied(left_position)) return false;
#ifndef NDEBUG
  }
  catch(std::runtime_error& e){
    std::cerr << e.what() << std::endl;
    throw std::runtime_error("Unexpected Error in IsLeftFlip");
  }
#endif
  if(red_or_blue[left_position] == turn) return false;
  
  const Card& left_card = GetCard(left_position);
  int left_element_mod = CorElement(left_card, left_position);
  int this_element_mod = CorElement(card, position);

  if(left_card.GetRight() + left_element_mod < card.GetLeft() + this_element_mod) return true;
  return false;
}


bool Board::IsRightFlip(const Card& card, int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in IsRightFlip(Card&, int)\n");
#endif
  if(position % 3 == 2) return false;

  int right_position = position + 1;
#ifndef NDEBUG
  try{
#endif
    if(!IsOccupied(right_position)) return false;
#ifndef NDEBUG
  }
  catch(std::runtime_error& e){
    std::cerr << e.what() << std::endl;
    std::string msg("Unexpected Error in IsRightFlip right_position = ");
    msg += std::to_string(right_position);
    msg += ", position = ";
    msg += std::to_string(position);
    throw std::runtime_error(msg);
  }
#endif
  if(red_or_blue[right_position] == turn) return false;
  
  const Card& right_card = GetCard(right_position);
  int right_element_mod = CorElement(right_card, right_position);
  int this_element_mod = CorElement(card, position);

  if(right_card.GetLeft() + right_element_mod < card.GetRight() + this_element_mod) return true;
  return false;
}

void Board::UpFlip(int position){
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in UpFlip(int)\n");
#endif
  int up_position = position - 3;

#ifndef NDEBUG
  if(up_position < 0 or 8 < up_position) throw std::runtime_error("position out of range in UpFlip(int)\n");
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
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in DownFlip(int)\n");
#endif
  int down_position = position + 3;

#ifndef NDEBUG
  if(down_position < 0 or 8 < down_position) throw std::runtime_error("position out of range in DownFlip(int)\n");
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
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in RightFlip(int)\n");
#endif
  int right_position = position + 1;

#ifndef NDEBUG
  if(right_position < 0 or 8 < right_position) throw std::runtime_error("position out of range in RightFlip(int)\n");
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
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in LeftFlip(int)\n");
#endif
  int left_position = position - 1;

#ifndef NDEBUG
  if(left_position < 0 or 8 < left_position) throw std::runtime_error("position out of range in LeftFlip(int)\n");
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

void Board::NormalFlip(const Card& card, int position){
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in NormalFlip(Card&, int)\n");
#endif
  if(IsUpFlip(card, position)) UpFlip(position);
  if(IsDownFlip(card, position)) DownFlip(position);
  if(IsRightFlip(card, position)) RightFlip(position);
  if(IsLeftFlip(card, position)) LeftFlip(position);
}

void Board::CascadeFlip(int position){
  if(position < 0 or 8 < position) return;
  if(!IsOccupied(position)) return;
  if(red_or_blue[position] == turn) return;

  red_or_blue[position] = turn;
  if(turn == Ally){
    --num_opponent_cards;
    ++num_ally_cards;
  } else{
    --num_ally_cards;
    ++num_opponent_cards;
  }
  
  const Card& card = GetCard(position);
  if(IsUpFlip(card, position)) CascadeFlip(position - 3);
  if(IsDownFlip(card, position)) CascadeFlip(position + 3);
  if(IsLeftFlip(card, position)) CascadeFlip(position - 1);
  if(IsRightFlip(card, position)) CascadeFlip(position + 1);
}

void Board::CascadeWithFlag(int position, int cascade_flag){
  switch(cascade_flag){
  case 0: // no same
    break;
  case 1: // up-right
    CascadeFlip(position - 3);
    CascadeFlip(position + 1);
    break;
  case 2:  // right-down
    CascadeFlip(position + 1);
    CascadeFlip(position + 3);
    break;
  case 3:  // down-left
    CascadeFlip(position + 3);
    CascadeFlip(position - 1);
    break;
  case 4:  // left-up
    CascadeFlip(position - 1);
    CascadeFlip(position - 3);
    break;
  case 5:  // up-down
    CascadeFlip(position - 3);
    CascadeFlip(position + 3);
    break;
  case 6:  // right-left
    CascadeFlip(position + 1);
    CascadeFlip(position - 1);
    break;
  case 7:  // up-right-down
    CascadeFlip(position - 3);
    CascadeFlip(position + 1);
    CascadeFlip(position + 3);
    break;
  case 8:  // right-down-left
    CascadeFlip(position + 1);
    CascadeFlip(position + 3);
    CascadeFlip(position - 1);
    break;
  case 9:  // down-left-up
    CascadeFlip(position + 3);
    CascadeFlip(position - 1);
    CascadeFlip(position - 3);
    break;
  case 10: // left-up-right
    CascadeFlip(position - 1);
    CascadeFlip(position - 3);
    CascadeFlip(position + 1);
    break;
  case 11: // all
    CascadeFlip(position - 3);
    CascadeFlip(position - 1);
    CascadeFlip(position + 1);
    CascadeFlip(position + 3);
    break;
  default: // never reached
#ifndef NDEBUG
    throw std::runtime_error("Never Reached Case in CascadeWithFlip");
#endif
    break;
  }
}



int Board::SameFlag(const Card& card, int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in SameFlag(Card&, int)\n");
#endif
  if(!IsEnableSame()) return 0;
  int up_card_num = 0;
  int down_card_num = 0;
  int right_card_num = 0;
  int left_card_num = 0;
#ifndef NDEBUG
  try{
#endif
    if(position > 2){
      if(IsOccupied(position - 3))
	up_card_num = GetCard(position - 3).GetDown();
    }
    else if(IsEnableWallSame())
      up_card_num = 10;
    
    if(position < 6){
      if(IsOccupied(position + 3))
	down_card_num = GetCard(position + 3).GetUp();
    }
    else if(IsEnableWallSame())
      down_card_num = 10;
    
    if(position % 3 != 2){
      if(IsOccupied(position + 1))
	right_card_num = GetCard(position + 1).GetLeft();
    }
    else if(IsEnableWallSame())
      right_card_num = 10;
    
    if(position % 3 != 0){
      if(IsOccupied(position - 1))
	left_card_num = GetCard(position - 1).GetRight();
    }
    else if(IsEnableWallSame())
      left_card_num = 10;
#ifndef NDEBUG
  }
  catch(std::runtime_error& e){
    std::cout << e.what() << std::endl;
    throw std::runtime_error("in SameFlag Unexpected Error");
  }
#endif
  bool up_same    = (up_card_num == card.GetUp());
  bool right_same = (right_card_num == card.GetRight());
  bool left_same  = (left_card_num == card.GetLeft());
  bool down_same  = (down_card_num == card.GetDown());

  if(up_same and right_same and left_same and down_same)
    return 11;
  if(left_same and up_same and right_same)
    return 10;
  if(down_same and left_same and up_same)
    return 9;
  if(right_same and down_same and left_same)
    return 8;
  if(up_same and right_same and down_same)
    return 7;
  if(right_same and left_same)
    return 6;
  if(up_same and down_same)
    return 5;
  if(left_same and up_same)
    return 4;
  if(down_same and left_same)
    return 3;
  if(right_same and down_same)
    return 2;
  if(up_same and right_same)
    return 1;
  return 0;
}

int Board::PlusFlag(const Card& card, int position) const{
#ifndef NDEBUG
  if(position < 0 or 8 < position) throw std::runtime_error("position out of range in PlusFlag(Card&, int)\n");
#endif
  if(!IsEnablePlus()) return 0;
  int up_card_num = 0;
  int down_card_num = 0;
  int right_card_num = 0;
  int left_card_num = 0;
#ifndef NDEBUG
  try{
#endif
    if(position > 2)
      if(IsOccupied(position - 3))
	up_card_num = GetCard(position - 3).GetDown();
    
    if(position < 6)
      if(IsOccupied(position + 3))
	down_card_num = GetCard(position + 3).GetUp();
    
    if(position % 3 != 2)
      if(IsOccupied(position + 1))
	right_card_num = GetCard(position + 1).GetLeft();
    
    if(position % 3 != 0)
      if(IsOccupied(position - 1))
	left_card_num = GetCard(position - 1).GetRight();
#ifndef NDEBUG
  }
  catch(std::runtime_error& e){
    std::cout << e.what() << std::endl;
    throw std::runtime_error("in PlusFlag Unexpected Error");
  }
#endif
  int up_sum    = up_card_num + card.GetUp();
  int down_sum  = down_card_num + card.GetDown();
  int right_sum = right_card_num + card.GetRight();
  int left_sum  = left_card_num + card.GetLeft();

  if(up_sum == down_sum and down_sum == right_sum and right_sum == left_sum)
    return 11;
  if(left_sum == up_sum and up_sum == right_sum)
    return 10;
  if(down_sum == left_sum and left_sum == up_sum)
    return 9;
  if(right_sum == down_sum and down_sum == left_sum)
    return 8;
  if(up_sum == right_sum and right_sum == down_sum)
    return 7;
  if(right_sum == left_sum)
    return 6;
  if(up_sum == down_sum)
    return 5;
  if(left_sum == up_sum)
    return 4;
  if(down_sum == left_sum)
    return 3;
  if(right_sum == down_sum)
    return 2;
  if(up_sum == right_sum)
    return 1;
  return 0;
}

