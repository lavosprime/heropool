/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  database.cc: Implementations of the application's database needs in terms of
    general database operations.

\******************************************************************************/

#include "./database.h"
#include "./db_impl.h"

#include <iostream>

using std::string;
using std::vector;

namespace heropool {

////////////////////////////////////////////////////////////////////////////////
//
//   SQL query format strings
//
// "kFooSQL" string constants are initialized to the contents of external files.
// During compilation, "foo.sql" is stripped of comments and blank lines, then
// the binary representation of the resulting text is formatted in hex as a C
// character-array initializer list and saved as "foo.sql.inc", which the
// definition of kFooSQL can directly #include.
//
////////////////////////////////////////////////////////////////////////////////

// Query format for inserting a (player, hero) tuple into the database.
const char kInsertSQL[] {
#include "insert.sql.inc"
};

// The magic ends here :)

////////////////////////////////////////////////////////////////////////////////
//
//   Function definitions
//
////////////////////////////////////////////////////////////////////////////////

Database::Database(
    std::unique_ptr<DBImpl> db);
    : db_{ std::move(db) } {
  if (db_->NeedsInit()) {
    // TODO set up the database
    db_->SetInitSuccessful();
  }
}

bool Database::InsertTuple(
    const string& player_name,
    const string& hero_name) {
  std::cerr << kInsertSQL;
  auto params = vector<string>{player, hero};
  return db_->PerformAction(kInsertSQL, params);
}

}  // namespace heropool

