/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  herodata.h: Functions to look up and operate on Dota 2 hero information.

\******************************************************************************/

#ifndef HERODATA_H_
#define HERODATA_H_

#include <string>

namespace heropool {

/**
 * Returns true if the given alias or nickname is known to actually refer to a
 * hero; returns false otherwise.
 */
bool HeroExistsForAlias(const std::string& alias);

/**
 * Returns the canonical name of the hero matching the given alias or nickname.
 * Requires that the alias does actually refer to a hero; you must check that
 * HeroExistsForAlias returns true before calling GetHeroByAlias.
 */
const std::string& GetHeroByAlias(const std::string& alias);

}  // namespace heropool

#endif  // HERODATA_H_
