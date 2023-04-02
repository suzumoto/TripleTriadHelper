#pragma once
#include <iostream>

enum Element{
  None,
  Fire,
  Thunder,
  Wind,
  Poison,
  Cold,
  Water,
  Ground,
  Holy
};

enum CardID{
  NullCard,
  
  Geezard = 101,
  Funguar,
  BiteBug,
  RedBat,
  Blobra,
  Gayla,
  Gesper,
  FastitocalonF,
  BloodSoul,
  Caterchipillar,
  Cockatrice,

  Grat = 201,
  Buel,
  Mesmerize,
  GlacialEye,
  Belhelmel,
  Thrustaevis,
  Anacondaur,
  Creeps,
  Grendel,
  Jelleye,
  GrandMantis,

  Forbidden = 301,
  Armadodo,
  TriFace,
  Fastitocalon,
  SnowLion,
  Ochu,
  SAM08G,
  DeathClaw,
  Cactuar,
  Tonberry,
  AbyssWorm,

  Turtapod = 401,
  Vysage,
  TRexaur,
  Bomb,
  Blitz,
  Wendigo,
  Torama,
  Imp,
  BlueDragon,
  Adamantoise,
  Hexadragon,

  IronGiant = 501,
  Behemoth,
  Chimera,
  PuPu,
  Elastoid,
  GIM47N,
  Malboro,
  RubyDragon,
  Elnoyle,
  TonberryKing,
  WedgeBiggs,

  FujinRaijin = 601,
  Elvoret,
  XATM092,
  Granaldo,
  Gerogero,
  Iguion,
  Abadon,
  Trauma,
  Oilboyle,
  ShumiTribe,
  Krysta,

  Propagator = 701,
  JumboCactuar,
  TriPoint,
  Gargantua,
  MobleType8,
  Sphinxara,
  Tiamat,
  BGH251F2,
  RedGiant,
  Catoblepas,
  UltimaWeapon,

  ChubbyChocobo = 801,
  Angelo,
  Gilgamesh,
  MiniMog,
  Chicobo,
  Quezacotl,
  Shiva,
  Ifrit,
  Siren,
  Sacred,
  Minotaur,

  Carbuncle = 901,
  Diablos,
  Leviathan,
  Odin,
  Pandemona,
  Cerberus,
  Alexander,
  Phoenix,
  Bahamut,
  Doomtrain,
  Eden,

  Ward = 1001,
  Kiros,
  Laguna,
  Selphie,
  Quistis,
  Irvine,
  Zell,
  Rinoa,
  Edea,
  Seifer,
  Squall
};

CardID& operator++(CardID& id);
CardID int_to_cardID(int id);


class Card{
private:
  enum CardID id;
  enum Element element;
  int up;
  int down;
  int left;
  int right;
public:
  Card();
  Card(enum CardID, int up, int right, int down, int left, enum Element);
  ~Card(){};
  enum CardID GetCardID() const{return id;}
  enum Element GetElement() const{return element;}
  int GetUp() const{return up;}
  int GetDown() const{return down;}
  int GetLeft() const{return left;}
  int GetRight() const{return right;}

  friend std::ostream& operator<<(std::ostream& os, const Card& card);
};

class CardData{
private:
  const int num_total_cards = 110;
  Card card_list[110];
public:
  CardData();
  ~CardData(){};
  Card& operator[](const enum CardID& id);
  const Card& operator[](const enum CardID& id) const;
};
