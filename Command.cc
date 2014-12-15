/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  Command.cc: Implementation of command processing.

*******************************************************************************/

#include "Command.h"
#include "Database.h"

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

void Command::Execute(Database& db) {
  for (auto arg : this->args_) {
    cout << arg << endl;
  }
}

bool Command::CausesExit(void) {
  return this->args_[0] == "quit";
}