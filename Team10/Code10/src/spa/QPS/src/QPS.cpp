#include "QPS.h"

namespace QPS {
std::list<std::string> QPS::evaluate(const std::string &query) {
  try {
    std::vector<std::shared_ptr<Token>> tokens = Tokenizer::tokenize(query);
    Validator::validate(tokens);

    std::vector<std::shared_ptr<Strategy>> strategies = Parser::parse(tokens);
    Optimizer::optimize(strategies);

    auto readFacade = ReadFacade();
    auto selectStrategy = Optimizer::getSelectStrategy();
    auto groups = Optimizer::getGroups();

    return Evaluator::getResultList(readFacade, selectStrategy, groups);
  } catch (SyntaxError &e) {
    std::cout << e.what() << std::endl;
    return {"SyntaxError"};

  } catch (SemanticError &e) {
    std::cout << e.what() << std::endl;
    return {"SemanticError"};

  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    return {"RuntimeError"};
  }
}
}  // namespace QPS