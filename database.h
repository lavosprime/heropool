/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  database.h: A class managing a database connection.

\******************************************************************************/

#ifndef DATABASE_H_
#define DATABASE_H_

#include <memory>
#include <string>
#include <vector>

namespace heropool {

class DBImpl;

// Abstracts away the SQL statements and result processing required to use a 
// database. Database provides only the few particular operations required by
// the rest of the program, implemented in terms of the more general operations
// provided by DBImpl's internal API.
class Database final {
 public:
  // Constructs a Database using the given DBImpl to perform its operations. If
  // this is the first time the database has been accessed, performs first-time
  // setup on the database so all of the required tables and such are in place.
  // Due to access restrictions on DBImpl, you will likely need to use a factory
  // function for some specific database implementation rather than calling
  // this constructor directly.
  explicit Database(
      std::unique_ptr<DBImpl> db);

  // Records (if not already recorded) that the given player plays the given
  // hero. Returns whether the operation completed successfully.
  bool InsertPlayerHeroPair(
      const string& player_name,
      const string& hero_name);

 private:
  // A "pimpl"-style handle to the internal API.
  unique_ptr<DBImpl> db_;
};

}  // namespace heropool

#endif  // DATABASE_H_

