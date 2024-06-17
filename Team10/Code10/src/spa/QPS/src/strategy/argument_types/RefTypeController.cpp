#include "strategy/argument_types/RefTypeController.h"

namespace QPS {
const std::unordered_map<RefType, SynonymType>
    RefTypeController::synonymTypeMap = {
        {RefType::IDENT, SynonymType::INVALID},
        {RefType::INTEGER, SynonymType::INVALID},
        {RefType::PROCEDURE_PROCNAME, SynonymType::PROCEDURE},
        {RefType::CALL_PROCNAME, SynonymType::CALL},
        {RefType::VARIABLE_VARNAME, SynonymType::VARIABLE},
        {RefType::READ_VARNAME, SynonymType::READ},
        {RefType::PRINT_VARNAME, SynonymType::PRINT},
        {RefType::CONSTANT_VALUE, SynonymType::CONSTANT},
        {RefType::STMT_STMTNO, SynonymType::STMT},
        {RefType::READ_STMTNO, SynonymType::READ},
        {RefType::PRINT_STMTNO, SynonymType::PRINT},
        {RefType::CALL_STMTNO, SynonymType::CALL},
        {RefType::WHILE_STMTNO, SynonymType::WHILE},
        {RefType::IF_STMTNO, SynonymType::IF},
        {RefType::ASSIGN_STMTNO, SynonymType::ASSIGN},
        {RefType::NONE, SynonymType::INVALID},
};

const std::unordered_map<RefType, AttrNameType>
    RefTypeController::attrNameTypeMap = {
        {RefType::IDENT, AttrNameType::NONE},
        {RefType::INTEGER, AttrNameType::NONE},
        {RefType::PROCEDURE_PROCNAME, AttrNameType::NAME},
        {RefType::CALL_PROCNAME, AttrNameType::NAME},
        {RefType::VARIABLE_VARNAME, AttrNameType::NAME},
        {RefType::READ_VARNAME, AttrNameType::NAME},
        {RefType::PRINT_VARNAME, AttrNameType::NAME},
        {RefType::CONSTANT_VALUE, AttrNameType::INTEGER},
        {RefType::STMT_STMTNO, AttrNameType::INTEGER},
        {RefType::READ_STMTNO, AttrNameType::INTEGER},
        {RefType::PRINT_STMTNO, AttrNameType::INTEGER},
        {RefType::CALL_STMTNO, AttrNameType::INTEGER},
        {RefType::WHILE_STMTNO, AttrNameType::INTEGER},
        {RefType::IF_STMTNO, AttrNameType::INTEGER},
        {RefType::ASSIGN_STMTNO, AttrNameType::INTEGER},
        {RefType::NONE, AttrNameType::NONE},
};

const std::unordered_set<RefType> RefTypeController::strictStmtTypes = {
    RefType::READ_STMTNO,  RefType::PRINT_STMTNO, RefType::CALL_STMTNO,
    RefType::WHILE_STMTNO, RefType::IF_STMTNO,    RefType::ASSIGN_STMTNO,
};

const std::unordered_set<RefType> RefTypeController::boolStrategyTypes = {
    RefType::INTEGER, RefType::IDENT};

bool RefTypeController::isBoolResult(RefType refType) {
  return boolStrategyTypes.count(refType) > 0;
}

bool RefTypeController::isStrictStmtType(RefType refType) {
  return strictStmtTypes.count(refType) > 0;
}

SynonymType RefTypeController::getSynonymType(RefType refType) {
  return synonymTypeMap.at(refType);
}

AttrNameType RefTypeController::getAttrNameType(RefType refType) {
  return attrNameTypeMap.at(refType);
}
}  // namespace QPS
