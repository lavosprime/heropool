/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  Database.h: A class abstracting a database connection.

*******************************************************************************/

#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>

extern "C" {
  #include "sqlite3.h"
}

// Abstracts away the SQL queries and SQLite API required to use a local
// database; instead, provides only the few particular operations required by
// the rest of the program.
class Database {
 public:
  // Connects to a database with the given filename, creating the file if it
  // does not exist. May fail, which will cause all other operations to fail.
  explicit Database(const std::string& filename);
  // Records (if not already recorded) that the given player plays the given
  // hero. Returns true if the transaction completed successfully.
  bool InsertTuple(const std::string& player, const std::string& hero);
  // Closes the database connection.
  ~Database();
 private:
  Database(const Database&) = delete;  // disable copy constructor
  Database& operator=(const Database&) = delete;  // disable assignment
  // A database access object from SQLite's API. NULL if constructor failed.
  sqlite3* db_;
};

#endif  // DATABASE_H_
