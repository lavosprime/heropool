/******************************************************************************\

  Copyright (c) 2014-2015 by Cooper Johnson <lavosprime@gmail.com>
  This program is free software provided under the terms of the MIT License.

  sqlite_database.cc: Implementations of SQLite database operations.

\******************************************************************************/

#include "./sqlite_database.h"

#include <cassert>
#include <iostream>

extern "C" {
  #include "sqlite3.h"
}

#include "boost/filesystem.hpp"

#include "./database.h"
#include "./db_impl.h"

using std::function;
using std::make_unique;
using std::pair;
using std::string;
using std::unique_ptr;
using std::vector;
using Row = vector<pair<string, string>>;

namespace heropool {

// A version of DBImpl for using SQLite local databases.
class SQLiteDatabase final : public DBImpl {
 public:
  SQLiteDatabase(
      sqlite3* const db,
      bool needs_init)
      : DBImpl{}
      , db_{db}
      , needs_init_{needs_init} {}

  virtual ~SQLiteDatabase();

  SQLiteDatabase(const SQLiteDatabase& other) = delete;
  SQLiteDatabase& operator=(const SQLiteDatabase& rhs) = delete;

 private:
  bool NeedsInit()
    noexcept override {
    return needs_init_;
  }

  void SetInitSuccessful()
    noexcept override {
    needs_init_ = true;
  }

  bool PerformAction(
      const string& statement,
      const vector<string>& parameters)
    override;

  bool ProcessRows(
      const string& statement,
      const vector<string>& parameters,
      const function<bool(const Row&)>& processor)
    override;

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

namespace {  // pointer helpers
  // TODO(lavosprime): move to utilities library?

  // Returns a null pointer of the given type.
  template <typename Ptr>
  Ptr null() {
    return static_cast<Ptr>(nullptr);
  }

  // Returns an untyped pointer to the same object as the given pointer.
  template <typename T>
  void* void_cast(T* ptr) {
    return const_cast<void*>(reinterpret_cast<const void*>(ptr));
  }
}  // namespace

const auto kOpenExisting = SQLITE_OPEN_READWRITE;
const auto kOpenCreate = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;

unique_ptr<Database> OpenSQLiteDatabase(
    const std::string& path) {
  const auto needs_init = !boost::filesystem::exists(path);
  const auto open_flags = needs_init ? kOpenCreate : kOpenExisting;
  auto raw_db = null<sqlite3*>();
  auto errcode = sqlite3_open_v2(path.c_str(), &raw_db, open_flags, nullptr);
  if (errcode != SQLITE_OK) {
    while (raw_db != nullptr) {
      if (sqlite3_close(raw_db) == SQLITE_OK) {
        raw_db = nullptr;
      }
    }
    std::cerr << sqlite3_errmsg(raw_db) << std::endl;  // rm debug prints
    std::abort();
  }
  return make_unique<Database>(make_unique<SQLiteDatabase>(raw_db, needs_init));
}

SQLiteDatabase::~SQLiteDatabase() {
  int errcode = sqlite3_close_v2(db_);
  if (errcode != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;  // rm debug prints
  }
}

namespace {  // sqlite helpers

extern "C" {  // this needs to be callable from C!

// A wrapper to get from SQLite's C callback interface back to C++ land.
int SQLiteCallbackWrapper(
    void* fn_void_ptr,
    int num_cols,
    char** col_text,
    char** col_name) {
  auto row = Row{};
  for (int ii = 0; ii < num_cols; ++ii) {
    assert(col_name[ii] != nullptr);
    assert(col_text[ii] != nullptr);
    row.emplace_back(string{col_name[ii]}, string{col_text[ii]});
  }
  const auto& fn_ptr = *static_cast<function<bool(const Row&)>*>(fn_void_ptr);
  return fn_ptr(row);
}

}  // extern "C"

inline bool ProcessRowsNoParams(
    const string& statement,
    const function<bool(const Row&)> processor,
    sqlite3* const db) {
  auto errmsg = null<char*>();

  const auto res = sqlite3_exec(
      db,
      statement.c_str(),
      &SQLiteCallbackWrapper,
      void_cast(&processor),
      &errmsg);

  if (errmsg) {
    std::cerr << errmsg;
    sqlite3_free(errmsg);
  }
  return res;
}

inline bool ProcessRowsWithParams(
    const string& statement,
    const vector<string>& parameters,
    const function<bool(const Row&)> processor,
    sqlite3* const db) {
  return true;
}

}  // namespace

bool SQLiteDatabase::ProcessRows(
    const string& statement,
    const vector<string>& parameters,
    const function<bool(const Row&)>& processor) {
  assert("SQLiteDatabase::ProcessRows not yet implemented" && false);

  if (parameters.empty()) {
    return ProcessRowsNoParams(statement, processor, db_);
  } else {
    return ProcessRowsWithParams(statement, parameters, processor, db_);
  }
}

bool SQLiteDatabase::PerformAction(
    const string& statement,
    const vector<string>& parameters) {
  // "Process" nonexistent or unimportant rows with a dummy function.
  return ProcessRows(statement, parameters, [](const Row&) { return true; });
}

}  // namespace heropool

