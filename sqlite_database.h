/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  sqlite_database.h: Declarations for connecting to a SQLite database.

\******************************************************************************/

#ifndef SQLITE_DATABASE_H_
#define SQLITE_DATABASE_H_

#include <memory>
#include <string>

namespace heropool {

class Database;

// Connects to a local SQLite database with the given path, creating the file if
// it does not exist, and returns a smart pointer to the database connection.
std::unique_ptr<Database> OpenSQLiteDatabase(
    const std::string& path);

}  // namespace heropool

#endif  // SQLITE_DATABASE_H_

