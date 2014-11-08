/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  Main.cc: Setup, teardown, and top-level command-line interface.

*******************************************************************************/

#include "HeroData.h"

#include <iostream>
#include <string>

int main(void) {
  std::string testAlias = "techies"
  if (HeroExistsForAlias(testAlias)) {
    std::cout << GetHeroByAlias(testAlias) << std::endl;
  }
}
