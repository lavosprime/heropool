/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  db_impl.h: An abstract class providing general database operations.

  DBImpl is considered an implementation detail of Database. Unless you are
  implementing Database or a derived class of DBImpl, you probably should not
  include this header.

\******************************************************************************/

#ifndef DB_IMPL_H_
#define DB_IMPL_H_

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace heropool {

class Database;

// DBImpl provides a simple API for general database operations that are used to
// build more specific database operations in Database. DBImpl is an abstract
// class, and constructors of derived classes should only be callable from
// factory functions that return std::unique_ptr<Database>. Derived classes may
// implement this API using any kind of persistent database.
class DBImpl {
 public:
  // Only Database can use the database API that DBImpl provides.
  friend class Database;

  // The destructor closes the database connection.
  virtual ~DBImpl() {};

  // Copying is disabled to prevent slicing and simplify resource ownership.
  DBImpl(const DBImpl&) final = delete;
  DBImpl& operator=(const DBImpl&) final = delete;

 protected:
  // The constructor opens the database connection. Only derived classes may
  // instantiate a DBImpl.
  DBImpl() {}

 private:
  // Returns whether the database needs first-time table setup.
  virtual bool NeedsInit()
    noexcept = 0;

  // Ensures that all future calls to NeedsInit will return true.
  virtual void SetInitSuccessful()
    noexcept = 0;

  // Performs some database action that does not return rows or whose returned
  // rows do not matter. The action takes the form of a statement that may be
  // parameterized and any parameters to the action. Returns whether the
  // operation completed successfully.
  virtual bool PerformAction(
      const std::string& statement,
      const std::vector<std::string>& parameters)
    = 0;

  // Calls a processor function on each row resulting from a query. The query
  // takes the form of a statement that may be paramaterized and any parameters
  // to the query. Each row is considered to take the form of a collection of
  // ordered pairs of (value, column name). The processor function must return
  // true if processing is to continue normally or false if processing is to be
  // aborted. ProcessRows returns whether the operation completed successfully.
  virtual bool ProcessRows(
      const std::string& statement,
      const std::vector<std::string>& parameters,
      const std::function<
          bool(const std::vector<std::pair<std::string, std::string>>&)
        >& processor)
    = 0;
};

}  // namespace heropool

#endif  // DB_IMPL_H_

