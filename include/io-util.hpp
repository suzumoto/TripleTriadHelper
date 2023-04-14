#pragma once
#include <unordered_map>
#include <utility>
#include <string>
#include "CardData.hpp"

class io_util
{
public:
  std::unordered_map<std::string, CardID> cardnum_to_id;
  io_util();
  ~io_util();
};
