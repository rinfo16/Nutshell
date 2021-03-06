#ifndef UPDATE_STMT_H__
#define UPDATE_STMT_H__

#include <string>
#include <vector>

#include "operation.h"
#include "parser/ast_base.h"
#include "parser/table_factor.h"
namespace ast {
class UpdateStmt : public ASTBase {
  friend ParserContext;
 public:
  UpdateStmt()
      : ASTBase(kASTUpdateStmt) {
  }
  const std::string & TableName() const {
    return table_name_;
  }

  std::vector<Operation *> & SetClauseList() {
    return set_clause_list_;
  }
  std::vector<TableFactor *> &OptFromClause() {
    return opt_from_clause_;
  }
  std::vector<ExpressionBase *> & OptWhere() {
    return opt_where_;
  }
  const std::vector<Operation *> & SetClauseList() const {
    return set_clause_list_;
  }
  const std::vector<TableFactor *> &OptFromClause() const {
    return opt_from_clause_;
  }
  const std::vector<ExpressionBase *> & OptWhere() const {
    return opt_where_;
  }
  virtual ptree ToPropertyTree() const;
 private:
  std::string table_name_;
  std::vector<Operation *> set_clause_list_;
  std::vector<TableFactor *> opt_from_clause_;
  std::vector<ExpressionBase *> opt_where_;
};
}
#endif // UPDATE_STMT_H__
