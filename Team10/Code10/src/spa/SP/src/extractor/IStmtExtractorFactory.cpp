#include "IStmtExtractorFactory.h"

#include "AssignExtractor.h"
#include "CallExtractor.h"
#include "DesignExtractor.h"
#include "IfExtractor.h"
#include "PrintExtractor.h"
#include "ReadExtractor.h"
#include "WhileExtractor.h"
#include "WriteFacade.h"

namespace SP {
const std::unordered_map<
    TokenType, std::function<std::unique_ptr<IStmtExtractor>(WriteFacade&)>>
    IStmtExtractorFactory::tokenTypeToExtractorMap = {
        {TokenType::READ,
         [](WriteFacade& w) { return std::make_unique<ReadExtractor>(w); }},
        {TokenType::ASSIGN,
         [](WriteFacade& w) { return std::make_unique<AssignExtractor>(w); }},
        {TokenType::PRINT,
         [](WriteFacade& w) { return std::make_unique<PrintExtractor>(w); }},
        {TokenType::IF,
         [](WriteFacade& w) { return std::make_unique<IfExtractor>(w); }},
        {TokenType::WHILE,
         [](WriteFacade& w) { return std::make_unique<WhileExtractor>(w); }},
        {TokenType::CALL,
         [](WriteFacade& w) { return std::make_unique<CallExtractor>(w); }}};

const std::unordered_map<TokenType, StatementType>
    IStmtExtractorFactory::tokenTypeToStatementTypeMap = {
        {TokenType::READ, StatementType::READ},
        {TokenType::ASSIGN, StatementType::ASSIGN},
        {TokenType::PRINT, StatementType::PRINT},
        {TokenType::IF, StatementType::IF},
        {TokenType::WHILE, StatementType::WHILE},
        {TokenType::CALL, StatementType::CALL}};

std::unique_ptr<IStmtExtractor> IStmtExtractorFactory::of(
    std::vector<std::unique_ptr<Token>>::iterator& it, WriteFacade& writer) {
  // start of statement, increment statement number
  DesignExtractor::incrementStmtNumber();
  int currentStmtNo = DesignExtractor::getStmtNumber();
  TokenType type = (*(it + 1))->getType() == TokenType::ASSIGN
                       ? (*(it + 1))->getType()
                       : (*it)->getType();
  writer.addStatement(tokenTypeToStatementTypeMap.at(type), currentStmtNo);
  return tokenTypeToExtractorMap.at(type)(writer);
}
}  // namespace SP
