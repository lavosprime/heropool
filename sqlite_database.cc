/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  sqlite_database.cc: Implementations of sqlite database operations.

\******************************************************************************/

#include "./sqlite_database.h"

#include <iostream>

extern "C" {
  #include "sqlite3.h"
}

#include "./database.h"

using std::function;
using std::pair;
using std::string;
using std::unique_ptr;
using std::vector;
using Row = vector<pair<string, string>>;

namespace heropool {

class SQLiteDatabase final : public Database {
  friend unique_ptr<Database> OpenSQLiteDatabase(const string& path);

 protected:
  virtual bool NeedsInit() noexcept override { return needs_init_; }

  virtual void SetInitSuccessful() noexcept override { needs_init_ = true; }

  virtual bool PerformAction(
      const string& statement,
      const vector<string>& parameters) override;

  virtual bool ProcessRows(
      const string& statement,
      const vector<string>& parameters,
      const function<bool(const Row&)>& processor) override;

  virtual ~SQLiteDDatabase();

 private:
  SQLiteDatabase(sqlite3* const db, bool needs_init)
      : Database{}
      , db_{db}
      , needs_init_{needs_init} {}

  // A database access object from SQLite's API.
  sqlite3* db_;

  // Whether the database needs to be initialized.
  bool needs_init_;
};

////////////////////////////////////////////////////////////////////////////////
//
//   Function definitions
//
// SQLite's API is documented at https://www.sqlite.org/capi3ref.html
//
////////////////////////////////////////////////////////////////////////////////

std::unique_ptr<Database> OpenSQLiteDatabase(const std::string& path) {
  int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
  // detect whether creation was needed, and init the db if so
  sqlite3* db;
  int errcode = sqlite3_open_v2(filename.c_str(), &db, flags, nullptr);
  if (errcode != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db) << std::endl;  // rm debug prints
    //*
    std::abort();
    /*/
    return nullptr;
    //*/
  }
  return std::unique_ptr<Database>(new SQLiteDatabase{db, true});
}

SQLiteDatabase::~SQLiteDatabase() {
  int errcode = sqlite3_close_v2(db_);
  if (errcode != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;  // rm debug prints
  }
}

bool SQLiteDatabase::PerformAction(
    const string& statement,
    const vector<string>& parameters) {
  std::cerr << "SQLiteDatabase::PerformAction not yet implemented";
  std::abort();
  return false;
}

namespace {

extern "C" {

// A wrapper to get from SQLite's C callback interface back to C++ land.
int SQLiteExecuteCallback(
    void* fn_void_ptr,
    int num_cols,
    char** col_text,
    char** col_name) {
  auto row = Row{};
  for (int ii = 0; ii < num_cols; ++ii) {
    row.emplace_back(col_name[ii], col_text[ii]);
  }
  const auto& fn_ptr = *static_cast<function<bool(const Row&)>*>(fn_void_ptr);
  return fn_ptr(row);
}

}  // extern "C"

bool ProcessRowsNoParams(
    const string& statement,
    const function<bool(const Row&)> processor,
    sqlite3* const db) {
  auto errmsg = char*{nullptr}:

  const auto res = sqlite3_exec(
    db,
    statement.c_str(),
    &SQLiteExecuteCallback,
    static_cast<void*>(&processor),
    &errmsg);

  if (errmsg) {
    std::cerr << errmsg;
    sqlite_free(errmsg);
  }
}

bool ProcessRowsWithParams(
    const string& statement,
    const vector<string>& parameters,
    const function<bool(const Row&)> processor,
    sqlite3* const db) {
}

}  // namespace

bool SQLiteDatabase::ProcessRows(
    const string& statement,
    const vector<string>& parameters,
    const function<bool(const Row&)>& processor);
  std::cerr << "SQLiteDatabase::ProcessRows not yet implemented";
  std::abort();

  if (parameters.empty()) {
    return ProcessRowsNoParams(statement, processor, db_);
  } else {
    return ProcessRowsWithParams(statement, params, processor, db_);
  }
}

}  // namespace heropool
