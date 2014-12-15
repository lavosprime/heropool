/*******************************************************************************

  Copyright (c) 2014 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  Database.cc: Implementations of database operations.

*******************************************************************************/

#include "Database.h"

#include <iostream>

#include "boost/format.hpp" // boost::format is like sprintf

using std::string;

////////////////////////////////////////////////////////////////////////////////
//
//   SQL query format strings
//
// "kFooSQL" string constants are initialized to the contents of external files.
// During compilation, "foo.sql" is stripped of comments and blank lines, then
// the binary representation of the resulting text is formatted in hex as a C
// character-array initializer list and saved as "foo.sql.inc", which the
// definition of kFooSQL can directly #include as a constructor argument.
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

Database::Database(const string& filename) {
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

bool Database::InsertTuple(const string& player, const string& hero) {
  std::cerr << kInsertSQL;
  auto query = boost::format(kInsertSQL) % player % hero;
  const char *cquery = query.str().c_str();
  std::cerr << cquery <<std::endl; // TODO remove debug prints
  // TODO send the query to the database engine
  return true;
}
