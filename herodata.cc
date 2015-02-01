/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  herodata.cc: Functions to look up and operate on Dota 2 hero information.

\******************************************************************************/

#include "./herodata.h"

#include <cassert>
#include <unordered_map>

using std::string;
using std::unordered_map;

namespace {

inline const unordered_map<string, string>& HeroesByAlias(void) {
  static const unordered_map<string, string> heroesByAlias {
#include "HeroesByAlias.inc"
  };
  return heroesByAlias;
}

}  // namespace

bool HeroExistsForAlias(const string& alias) {
  return HeroesByAlias().count(alias) == 1;
}

const string& GetHeroByAlias(const string& alias) {
  assert(HeroExistsForAlias(alias));
  return HeroesByAlias().at(alias);
}
