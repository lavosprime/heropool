/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  database.h: A class abstracting a database connection.

\******************************************************************************/

#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>

extern "C" {
  #include "sqlite3.h"
}

// Abstracts away the SQL queries and SQLite API required to use a local
// database; instead, provides only the few particular operations required by
// the rest of the program.
class Database final {
 public:
  // Connects to a database with the given filename, creating the file if it
  // does not exist. May fail, which will cause all other operations to fail.
  explicit Database(const std::string& filename) : db_(OpenDB(filename)) {}
  // Records (if not already recorded) that the given player plays the given
  // hero. Returns true if the transaction completed successfully.
  bool InsertTuple(const std::string& player, const std::string& hero);
  // Closes the database connection.
  ~Database();
 private:
  Database(const Database&) = delete;  // disable copy constructor
  Database& operator=(const Database&) = delete;  // disable assignment
  // Returns a database object from SQLite's API connected to a database with
  // the given filename, creating the file if it does not exist, or nullptr
  // if opening the database connection failed.
  static sqlite3* OpenDB(const std::string& filename);
  // A database access object from SQLite's API. nullptr if constructor failed.
  sqlite3* db_;
};

#endif  // DATABASE_H_
