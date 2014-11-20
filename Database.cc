/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  Database.cc: Implementations of database operations.

*******************************************************************************/

#include "Database.h"

#include <iostream>
#include <sstream>
#include <string>

#include <boost/format.hpp>  // boost::format is like stream-friendly sprintf
#include <sqlite3.h>

using std::string;
using std::stringstream;

////////////////////////////////////////////////////////////////////////////////
//
//   SQL query format strings
//
// "kFooSQL" string constants are initialized to the contents of external files.
// During compilation, "foo.sql" is stripped of comments and hex-dumped to
// "foo.sql.inc" as a character-array initializer list, which the definition of
// kFooSQL can directly #include.
//
////////////////////////////////////////////////////////////////////////////////

// Query format for inserting a (player, hero) tuple into the database.
static const string kInsertSQL({
#include "insert.sql.inc"
});

////////////////////////////////////////////////////////////////////////////////
//
//   Function definitions
//
////////////////////////////////////////////////////////////////////////////////

Database::Database(const string &filename) {
  int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
  // TODO detect whether creation was needed, and init the db if so
  int errcode = sqlite3_open_v2(filename.c_str(), &(this->db_), flags, nullptr);
  if (errcode != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(this->db_) << std::endl; // TODO rm debug prints
  }
}

Database::~Database() {
  int errcode = sqlite3_close_v2(this->db_);
  if (errcode != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(this->db_) << std::endl; // TODO rm debug prints
  }
}

bool InsertTuple(const string &player, const string &hero) {
  std::stringstream query;
  query << boost::format(kInsertSQL) % player % hero;
  const char *cquery = query.str().c_str();
  std::cerr << cquery <<std::endl; // TODO remove debug prints
  // TODO send the query to the database engine
  return true;
}
