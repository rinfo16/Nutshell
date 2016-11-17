#include "executor/compare.h"

StringCompare::StringCompare(OperatorType op, ValueExprInterface *left,
    ValueExprInterface *right)
: op_(op),
left_(left),
right_(right) {
}

bool StringCompare::GetValue(TupleRow *row) {
  char *str;
  uint32_t len;
  str = (char*)left_->GetValue(row, &len);
  std::string str_left(str, len);
  str = (char*)right_->GetValue(row, &len);
  std::string str_right(str, len);
  switch (op_) {
    case kEqual:
      return str_left == str_right;
      break;
    case kLess:
      return str_left < str_right;
      break;
    case kGreater:
      return str_left > str_right;
      break;
    case kLessOrEqual:
      return str_left <= str_right;
      break;
    case kGreaterOrEaual:
      return str_left >= str_right;
      break;
    default:
      break;
  }
  return false;
}

IntegerCompare::IntegerCompare(OperatorType op, ValueExprInterface *left,
                               ValueExprInterface *right)
    : op_(op),
      left_(left),
      right_(right) {
}

bool IntegerCompare::GetValue(TupleRow *row) {
  uint32_t len;
  int64_t int_left = *(uint64_t*)left_->GetValue(row, &len);
  int64_t int_right = *(uint64_t*)right_->GetValue(row, &len);
  switch (op_) {
    case kEqual:
      return int_left == int_right;
      break;
    case kLess:
      return int_left < int_right;
      break;
    case kGreater:
      return int_left > int_right;
      break;
    case kLessOrEqual:
      return int_left <= int_right;
      break;
    case kGreaterOrEaual:
      return int_left >= int_right;
      break;
    default:
      break;
  }
  return false;
}

FloatCompare::FloatCompare(OperatorType op, ValueExprInterface *left,
                           ValueExprInterface *right)
    : op_(op),
      left_(left),
      right_(right) {
}

bool FloatCompare::GetValue(TupleRow *row) {
  uint32_t len;
  double_t float_left = *(double*)left_->GetValue(row, &len);
  double_t float_right = *(double*)right_->GetValue(row, &len);
  switch (op_) {
    case kEqual:
      return float_left == float_right;
      break;
    case kLess:
      return float_left < float_right;
      break;
    case kGreater:
      return float_left > float_right;
      break;
    case kLessOrEqual:
      return float_left <= float_right;
      break;
    case kGreaterOrEaual:
      return float_left >= float_right;
      break;
    default:
      break;
  }
  return false;
}
