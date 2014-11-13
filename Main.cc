/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  Main.cc: Setup, teardown, and user input.

*******************************************************************************/

#include "HeroData.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

static const string workingDirWarning =
    "Warning: heropool was not launched from its own directory.";

static bool ProcessSingleCommand(vector<string> commandArgs);
static void ProcessCommandsInteractively(void);
static void WarnAboutWorkingDirectory(string arg0);

int main(int argc, char **argv) {
  if (argc > 0) {
    WarnAboutWorkingDirectory(argv[0]);
  }
  if (argc > 1) {
    vector<string> commandArgs(argv + 1, argv + argc);
    ProcessSingleCommand(commandArgs);
  } else {
    ProcessCommandsInteractively();
  }
  return 0;
}

static void WarnAboutWorkingDirectory(string arg0) {
  if (arg0 != "./heropool") {
    cout << workingDirWarning << endl;
  }
}

static bool ProcessSingleCommand(vector<string> commandArgs) {
  for (auto arg : commandArgs) {
    cout << arg << endl;
  }
  // Command cmd(commandArgs);
  // cmd.run();
  return 0; // return !cmd.causesExit();
}

static void ProcessCommandsInteractively(void) {
  bool shouldContinue = true;
  while (shouldContinue) {
    string inputLine;
    getline(cin, inputLine);
    vector<string> commandArgs;
    boost::split(commandArgs, inputLine, boost::is_any_of("\t "));
    shouldContinue = ProcessSingleCommand(commandArgs);
  }
}
