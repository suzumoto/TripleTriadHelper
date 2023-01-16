#pragma once

enum SpecialRule{
  OPEN,
  SUDDEN_DEATH,
  RANDOM_HAND,
  SAME,
  PLUS,
  WALL_SAME,
  ELEMENTAL
};

class Rules{
private:
  const int num_total_rules = 7;
  int num_enable_rules;
  bool enable_list[7];
public:
  Rules();
  Rules(bool open, bool sudden_death, bool random_hand, bool same,
	bool plus, bool wall_same, bool elemental);
  ~Rules(){};
  void EnableOpen();
  void EnableSuddenDeath();
  void EnableRandomHand();
  void EnableSame();
  void EnablePlus();
  void EnableWallSame();
  void EnableElemental();

  void DisableOpen();
  void DisableSuddenDeath();
  void DisableRandomHand();
  void DisableSame();
  void DisablePlus();
  void DisableWallSame();
  void DisableElemental();
  
  bool IsEnableOpen() const{return enable_list[OPEN];}
  bool IsEnableSuddenDeath() const{return enable_list[SUDDEN_DEATH];}
  bool IsEnableRandomHand() const{return enable_list[RANDOM_HAND];}
  bool IsEnableSame() const{return enable_list[SAME];}
  bool IsEnablePlus() const{return enable_list[PLUS];}
  bool IsEnableWallSame() const{return enable_list[WALL_SAME];}
  bool IsEnableElemental() const{return enable_list[ELEMENTAL];}
  
  int GetNumEnableRules() const{return num_enable_rules;}
};
