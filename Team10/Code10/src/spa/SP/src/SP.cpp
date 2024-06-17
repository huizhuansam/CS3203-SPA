#include "SP.h"

#include <memory>
#include <vector>

#include "extractor/DesignExtractor.h"
#include "parser/Parser.h"
#include "tokenizer/Tokenizer.h"

namespace SP {
void SP::processSimple(const std::string& input) {
  std::vector<std::unique_ptr<Token>> tokens = Tokenizer::tokenize(input);
  Parser::parse(tokens);
  DesignExtractor::extract(tokens);
};
}  // namespace SP
