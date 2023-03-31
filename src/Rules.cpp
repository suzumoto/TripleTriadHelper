#include <Rules.hpp>

Rules::Rules(){
  num_enable_rules = 0;
  for(int i = 0; i < num_total_rules; ++i){
    enable_list[i] = false;
  }
}

Rules::Rules(bool open, bool sd, bool rh, bool same, bool plus, bool wsame, bool el){
  enable_list[OPEN] = open;
  enable_list[SUDDEN_DEATH] = sd;
  enable_list[RANDOM_HAND] = rh;
  enable_list[SAME] = same;
  enable_list[PLUS] = plus;
  enable_list[WALL_SAME] = wsame;
  enable_list[ELEMENTAL] = el;
  num_enable_rules = 0;
  for(int i = 0; i < num_total_rules; ++i){
    if(enable_list[i]) ++num_enable_rules;
  }
}

void Rules::EnableOpen(){
  if(!enable_list[OPEN]) ++num_enable_rules;
  enable_list[OPEN] = true;
}

void Rules::EnableSuddenDeath(){
  if(!enable_list[SUDDEN_DEATH]) ++num_enable_rules;
  enable_list[SUDDEN_DEATH] = true;
}

void Rules::EnableRandomHand(){
  if(!enable_list[RANDOM_HAND]) ++num_enable_rules;
  enable_list[RANDOM_HAND] = true;
}

void Rules::EnableSame(){
  if(!enable_list[SAME]) ++num_enable_rules;
  enable_list[SAME] = true;
}

void Rules::EnablePlus(){
  if(!enable_list[PLUS]) ++num_enable_rules;
  enable_list[PLUS] = true;
}

void Rules::EnableWallSame(){
  if(!enable_list[WALL_SAME]) ++num_enable_rules;
  enable_list[WALL_SAME] = true;
}

void Rules::EnableElemental(){
  if(!enable_list[ELEMENTAL]) ++num_enable_rules;
  enable_list[ELEMENTAL] = true;
}

void Rules::DisableOpen(){
  if(enable_list[OPEN]) --num_enable_rules;
  enable_list[OPEN] = false;
}

void Rules::DisableSuddenDeath(){
  if(enable_list[SUDDEN_DEATH]) --num_enable_rules;
  enable_list[SUDDEN_DEATH] = false;
}

void Rules::DisableRandomHand(){
  if(enable_list[RANDOM_HAND]) --num_enable_rules;
  enable_list[RANDOM_HAND] = false;
}

void Rules::DisableSame(){
  if(enable_list[SAME]) --num_enable_rules;
  enable_list[SAME] = false;
}

void Rules::DisablePlus(){
  if(enable_list[PLUS]) --num_enable_rules;
  enable_list[PLUS] = false;
}

void Rules::DisableWallSame(){
  if(enable_list[WALL_SAME]) --num_enable_rules;
  enable_list[WALL_SAME] = false;
}

void Rules::DisableElemental(){
  if(enable_list[ELEMENTAL]) --num_enable_rules;
  enable_list[ELEMENTAL] = false;
}

bool operator==(const Rules& rhs, const Rules& lhs){
  if(rhs.num_enable_rules != lhs.num_enable_rules) return false;
  for(int i = 0; i < rhs.num_total_rules; ++i){
    if(rhs.enable_list[i] != lhs.enable_list[i]) return false;
  }
  return true;
}

bool operator!=(const Rules& rhs, const Rules& lhs){
  return !(rhs == lhs);
}
