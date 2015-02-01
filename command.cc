/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  command.cc: Implementation of command processing.

\******************************************************************************/

#include "./command.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void Command::Execute(const Database* db) {
  for (auto arg : this->args_) {
    cout << arg << endl;
  }
}

bool Command::CausesExit(void) {
  return this->args_[0] == "quit";
}
