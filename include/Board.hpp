#pragma once
#include <vector>
#include <utility>
#include <Rules.hpp>
#include <CardData.hpp>
enum Player{
  Unoccupied,
  Ally,
  Opponent
};

class Board{
private:
  CardData card_data;
  const int num_positions = 9;
  Rules rules;
  enum Element element_list[9];
  enum Player red_or_blue[9];
  enum CardID card_list[9];
  enum Player turn;
  enum Player sente;
  int num_opponent_cards;
  int num_ally_cards;
  int num_unoccupied_positions;
  bool is_game_end;
  
  const int num_total_cards = 5;
  std::vector<enum CardID> ally_card_list;
  std::vector<enum CardID> opponent_card_list;
  
public:
  Board(enum CardID ally_card_list[5], enum CardID opponent_card_list[5], Rules, enum Player turn);
  Board(enum CardID ally_card_list[5], enum CardID opponent_card_list[5], Rules, enum Player turn, enum Element element_list[9]);
  Board(const Board& board);
  ~Board(){};
  void SetElement(enum Element el, int position);
  enum Element GetElement(int position) const;
  bool IsOccupied(int position) const;
  bool IsGameEnd() const;
  enum Player GetTurnPlayer() const;
  const std::vector<enum CardID>& GetAllyCardList() const{return ally_card_list;};
  const std::vector<enum CardID>& GetOpponentCardList() const{return opponent_card_list;};
  const std::vector<enum CardID>& GetTurnPlayerCardList() const;
  enum Player GetWinner() const;
  const Card& GetCard(int position) const;
  void SetTurn(enum Player player);
  void Play(int index, int position);
  void ForceCardOnBoard(enum Player srcPlayer, int index, int position, enum Player dstPlayer);
  int MoveEval(int index, int position) const; // -1 lose, 0 draw, 1 win
  int MoveEval(int index, int position, long& count) const; // -1 lose, 0 draw, 1 win
  std::pair<int, int> BestSearch() const;
  friend std::ostream& operator<<(std::ostream& os, const Board& board);
  friend bool operator==(const Board& rhs, const Board& lhs);
  friend bool operator!=(const Board& rhs, const Board& lhs){return !(rhs == lhs);}
  
protected:
  bool IsEnableSame() const;
  bool IsEnablePlus() const;
  bool IsEnableWallSame() const;
  bool IsEnableElemental() const;
  int CorElement(const Card& card, int position) const;
  bool IsUpFlip(const Card& card, int position) const;
  bool IsDownFlip(const Card& card, int position) const;
  bool IsRightFlip(const Card& card, int position) const;
  bool IsLeftFlip(const Card& card, int position) const;
  void UpFlip(int position);
  void DownFlip(int position);
  void RightFlip(int position);
  void LeftFlip(int position);
  void NormalFlip(const Card& card, int position);
  void CascadeFlip(int position);
  void CascadeWithFlag(int position, int cascade_flag);
  int SameFlag(const Card& card, int position) const;
      /* 0 (no same), 1(up-right) 2(right-down), 3(down-left), 4(left-up),
	 5 (up-down), 6(right-left), 7(up-right-down), 8(right-down-left),
         9 (down-left-up), 10 (left-up-right), 11(all) */
  int PlusFlag(const Card& card, int position) const;
};
