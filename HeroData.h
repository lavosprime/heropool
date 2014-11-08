/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  HeroData.h: Functions to look up and operate on Dota 2 hero information.

*******************************************************************************/

#ifndef _HEROPOOL_HERODATA_H_
#define _HEROPOOL_HERODATA_H_

#include <string>

const bool HeroExistsForAlias(const std::string& alias);

const std::string& GetHeroByAlias(const std::string& alias);

#endif  // _HEROPOOL_HERODATA_H_
