/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  Main.cc: Setup, teardown, and user input.

*******************************************************************************/

#include "Command.h"
#include "Database.h"
#include "HeroData.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>  // boost::split to split strings

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

static const string workingDirWarning =
    "Warning: heropool was not launched from its own directory.";

static bool ProcessSingleCommand(Database& db, vector<string>& commandArgs);
static void ProcessCommandsInteractively(Database& db);
static void WarnAboutWorkingDirectory(string arg0);

int main(int argc, char** argv) {
  Database db("./heropool.db");
  if (argc > 0) {
    WarnAboutWorkingDirectory(argv[0]);
  }
  if (argc > 1) {
    vector<string> commandArgs(argv + 1, argv + argc);
    ProcessSingleCommand(db, commandArgs);
  } else {
    ProcessCommandsInteractively(db);
  }
  return 0;
}

static void WarnAboutWorkingDirectory(string arg0) {
  if (arg0 != "./heropool") {
    cout << workingDirWarning << endl;
  }
}

static bool ProcessSingleCommand(Database& db, vector<string>& commandArgs) {
  if (commandArgs.size() == 0) {
    return true;
  }
  Command cmd(commandArgs);
  cmd.Execute(db);
  return !cmd.CausesExit();
}

static void ProcessCommandsInteractively(Database& db) {
  bool shouldContinue = true;
  while (shouldContinue) {
    string inputLine;
    std::getline(cin, inputLine);
    vector<string> commandArgs;
    boost::split(commandArgs, inputLine, boost::is_any_of("\t "));
    shouldContinue = ProcessSingleCommand(db, commandArgs);
  }
}
