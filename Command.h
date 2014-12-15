/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  Command.h: Wrapper around processing of user commmands.

*******************************************************************************/

#ifndef COMMAND_H_
#define COMMAND_H_

#include "Database.h"

#include <string>
#include <vector>

#include <boost/utility.hpp>

using std::string;
using std::vector;

// Handles a single user command based on the arguments provided by the user.
class Command : boost::noncopyable {
 public:
  // Creates a Command that uses the given arguments for execution.
  explicit Command(vector<string>& args) : args_(args) {}
  // Performs the action specified by the command arguments.
  void Execute(Database& db);
  // Returns whether the program should end after execution of this command.
  bool CausesExit(void);
 private:
  vector<string>& args_;
};

#endif  // COMMAND_H_
