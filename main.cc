/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  main.cc: Setup, teardown, and user input.

\******************************************************************************/

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "boost/algorithm/string.hpp"  // boost::split to split strings

#include "./command.h"
#include "./database.h"
#include "./db_impl.h"
#include "./herodata.h"
#include "./sqlite_database.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

using heropool::Command;
using heropool::Database;
using heropool::OpenSQLiteDatabase;

const char workingDirWarning[] =
    "Warning: heropool was not launched from its own directory.";

namespace {

bool ProcessSingleCommand(Database* const db,
                          const vector<string>& commandArgs) {
  if (commandArgs.size() == 0) {
    return true;
  }
  auto cmd = Command(commandArgs);
  cmd.Execute(db);
  return !cmd.CausesExit();
}

void ProcessCommandsInteractively(Database* const db) {
  bool shouldContinue = true;
  while (shouldContinue) {
    string inputLine;
    std::getline(cin, inputLine);
    vector<string> commandArgs;
    boost::split(commandArgs, inputLine, boost::is_any_of("\t "));
    shouldContinue = ProcessSingleCommand(db, commandArgs);
  }
}

void WarnAboutWorkingDirectory(const string& arg0) {
  if (arg0 != "./heropool") {
    cout << workingDirWarning << endl;
  }
}

}  // namespace

int main(int argc, char* argv[]) {
  auto db = OpenSQLiteDatabase("./heropool.db");
  if (argc > 0) {
    WarnAboutWorkingDirectory(argv[0]);
  }
  if (argc > 1) {
    auto commandArgs = vector<string>(argv + 1, argv + argc);
    ProcessSingleCommand(db.get(), commandArgs);
  } else {
    ProcessCommandsInteractively(db.get());
  }
  return 0;
}

