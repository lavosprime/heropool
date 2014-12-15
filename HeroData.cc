/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  HeroData.cc: Functions to look up and operate on Dota 2 hero information.

*******************************************************************************/

#include "HeroData.h"

#include <cassert>
#include <map>

using std::string;

static std::map<string, string> heroesByAlias {
#include "HeroesByAlias.inc"
};

const bool HeroExistsForAlias(const string& alias) {
  return heroesByAlias.count(alias) == 1;
}

const string& GetHeroByAlias(const string& alias) {
  assert(HeroExistsForAlias(alias));
  return heroesByAlias[alias];
}
