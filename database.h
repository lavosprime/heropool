/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  database.h: A class abstracting a database connection.

\******************************************************************************/

#ifndef DATABASE_H_
#define DATABASE_H_

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace heropool {

// Abstracts away the SQL statements and result processing required to use a 
// database. Database provides only the few particular operations required by
// the rest of the program, and derived classes implement the underlying general
// database operations in the form of an internal API of protected pure virtual
// functions.
class Database {
  using std::function;
  using std::pair;
  using std::string;
  using std::vector;

 public:
  // Records (if not already recorded) that the given player plays the given
  // hero. Returns whether the operation completed successfully.
  bool InsertPlayerHeroPair(const string& player, const string& hero) final;

  // Copying is disabled so implementations don't have to worry about 

  // Disable copy construction.
  Database(const Database&) final = delete;
  // Disable copy assignment.
  Database& operator=(const Database&) final = delete;

 protected:
  using Row = vector<pair<string, string>>

  // The constructor opens the database connection, but it should only be called
  // from a factory function that returns a unique_ptr<Database>.
  Database() {}

  // Return whether the database needs initialization (first-time table setup).
  virtual bool NeedsInit() noexcept = 0;

  // Ensure that all future calls to NeedsInit will return true.
  virtual void SetInitSuccessful() noexcept = 0;

  // Perform some database action that does not return rows or whose returned
  // rows do not matter. The action takes the form of a statement that may be
  // parameterized and any parameters to the action. Returns whether the
  // operation completed successfully.
  virtual bool PerformAction(
      const string& statement,
      const vector<string>& parameters) = 0;

  // Call a processor function on each Row resulting from a query. The query
  // takes the form of a statement that may be paramaterized and any parameters
  // to the query. The processor function must return true if processing is to
  // continue normally or false if processing is to be aborted. ProcessRows
  // returns whether the operation completed successfully.
  virtual bool ProcessRows(
      const string& statement,
      const vector<string>& parameters,
      const function<bool(const vector<pair<string, string>>&)>& processor) = 0;

  // Close the database connection.
  virtual ~Database();

};

}  // namespace heropool

#endif  // DATABASE_H_
