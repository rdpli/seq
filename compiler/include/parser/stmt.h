#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "parser/expr.h"
#include "parser/pattern.h"
#include "parser/visitor.h"

using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::pair;

struct Param {
  string name;
  ExprPtr type;
  ExprPtr deflt;
  string to_string() const;
};

struct Stmt : public seq::SrcObject {
  virtual ~Stmt() {}
  virtual string to_string() const = 0;
  virtual void accept(StmtVisitor &) = 0;
  friend ostream &operator<<(ostream &out, const Stmt &c) {
    return out << c.to_string();
  }
};

typedef unique_ptr<Stmt> StmtPtr;
typedef vector<StmtPtr> StmtSuite;

#define ACCEPT_VISITOR                                                      \
  virtual void accept(StmtVisitor &visitor) { visitor.visit(*this); }

struct PassStmt : public Stmt {
  PassStmt();
  string to_string() const;
  ACCEPT_VISITOR;
};

struct BreakStmt : public Stmt {
  BreakStmt();
  string to_string() const;
  ACCEPT_VISITOR;
};

struct ContinueStmt : public Stmt {
  ContinueStmt();
  string to_string() const;
  ACCEPT_VISITOR;
};

struct ExprStmt : public Stmt {
  ExprPtr expr;
  ExprStmt(ExprPtr e);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct AssignStmt : public Stmt {
  ExprPtr lhs, rhs, type;
  int kind; // 0 normal 1 shadow 2 update
  AssignStmt(ExprPtr l, ExprPtr r, int k, ExprPtr t);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct DelStmt : public Stmt {
  ExprPtr expr;
  DelStmt(ExprPtr e);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct PrintStmt : public Stmt {
  vector<ExprPtr> items;
  string terminator;
  PrintStmt(vector<ExprPtr> i, string t);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct ReturnStmt : public Stmt {
  ExprPtr expr;
  ReturnStmt(ExprPtr e);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct YieldStmt : public Stmt {
  ExprPtr expr;
  YieldStmt(ExprPtr e);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct AssertStmt : public Stmt {
  ExprPtr expr;
  AssertStmt(ExprPtr e);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct TypeAliasStmt : public Stmt {
  string name;
  ExprPtr expr;
  TypeAliasStmt(string n, ExprPtr e);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct WhileStmt : public Stmt {
  ExprPtr cond;
  StmtSuite suite;
  WhileStmt(ExprPtr c, StmtSuite s);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct ForStmt : public Stmt {
  vector<string> vars;
  ExprPtr iter;
  StmtSuite suite;
  ForStmt(vector<string> v, ExprPtr i, StmtSuite s);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct IfStmt : public Stmt {
  struct If {
    ExprPtr cond;
    StmtSuite suite;
  };
  vector<If> ifs;
  IfStmt(vector<If> i);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct MatchStmt : public Stmt {
  ExprPtr what;
  vector<pair<PatternPtr, StmtSuite>> cases;
  MatchStmt(ExprPtr w, vector<pair<PatternPtr, StmtSuite>> c);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct ExtendStmt : public Stmt {
  ExprPtr what;
  StmtSuite suite;
  ExtendStmt(ExprPtr e, StmtSuite s);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct ImportStmt : public Stmt {
  typedef pair<string, string> Item;
  Item from;
  vector<Item> what;
  ImportStmt(Item f, vector<Item> w);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct ExternImportStmt : public Stmt {
  ImportStmt::Item name;
  ExprPtr from;
  ExprPtr ret;
  vector<Param> args;
  string lang;
  ExternImportStmt(ImportStmt::Item n, ExprPtr f, ExprPtr t, vector<Param> a, string l);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct TryStmt : public Stmt {
  struct Catch {
    string var;
    ExprPtr exc;
    StmtSuite suite;
  };
  StmtSuite suite;
  vector<Catch> catches;
  StmtSuite finally;

  TryStmt(StmtSuite s, vector<Catch> c, StmtSuite f);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct GlobalStmt : public Stmt {
  string var;
  GlobalStmt(string v);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct ThrowStmt : public Stmt {
  ExprPtr expr;
  ThrowStmt(ExprPtr e);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct PrefetchStmt : public Stmt {
  vector<ExprPtr> what;
  PrefetchStmt(vector<ExprPtr> w);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct FunctionStmt : public Stmt {
  string name;
  ExprPtr ret;
  vector<string> generics;
  vector<Param> args;
  StmtSuite suite;
  vector<string> attributes;
  FunctionStmt(string n, ExprPtr r, vector<string> g, vector<Param> a, StmtSuite s, vector<string> at);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct ClassStmt : public Stmt {
  bool is_type;
  string name;
  vector<string> generics;
  vector<Param> args;
  StmtSuite suite;
  ClassStmt(bool i, string n, vector<string> g, vector<Param> a, StmtSuite s);
  string to_string() const;
  ACCEPT_VISITOR;
};

struct DeclareStmt : public Stmt {
  Param param;
  DeclareStmt(Param p);
  string to_string() const;
  ACCEPT_VISITOR;
};

#undef ACCEPT_VISITOR
