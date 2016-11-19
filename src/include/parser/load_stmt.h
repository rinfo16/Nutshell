#ifndef LOAD_STMT_H__
#define LOAD_STMT_H__
#include "parser/ast_base.h"
#include <string>
#include <vector>
namespace ast {
class LoadStmt : public ASTBase {
  friend ParserContext;
 public:
  LoadStmt() : ASTBase(kASTCopyStmt) {
  }
  const std::string & TableName() const {
    return table_name_;
  }
  const std::string & FilePath() const {
    return file_path_;
  }
  const std::vector<std::string> & OptColumnNameList() const {
    return opt_column_name_list_;
  }
  virtual ptree ToPropertyTree() const;
 private:
  std::string table_name_;
  std::string file_path_;
  std::vector<std::string> opt_column_name_list_;
};
}
#endif // LOAD_STMT_H__
