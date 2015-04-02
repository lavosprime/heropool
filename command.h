/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  command.h: Wrapper around processing of user commmands.

\******************************************************************************/

#ifndef COMMAND_H_
#define COMMAND_H_

#include <algorithm>
#include <string>
#include <vector>

#include "./database.h"

// Handles a single user command based on the arguments provided by the user.
class Command final {
 public:
  // Creates a Command that uses the given arguments for execution.
  explicit Command(std::vector<std::string> args) : args_(std::move(args)) {}
  // Performs the action specified by the command arguments.
  void Execute(const Database* db);
  // Returns whether the program should end after execution of this command.
  bool CausesExit(void);
  // Use compiler-provided move construction and move assignment.
  Command(Command&&) = default;
  Command& operator=(Command&&) = default;
 private:
  // Disable copy construction and copy assignment.
  Command(const Command&) = delete;
  Command& operator=(const Command&) = delete;
  // The arguments to the command.
  std::vector<std::string> args_;
};

#endif  // COMMAND_H_
