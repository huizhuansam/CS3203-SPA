#include "strategy/Strategy.h"
#include "strategy/TupleSelectStrategy.h"
#include "strategy/WithStrategy.h"

using namespace QPS;

namespace Strategies {

// Select procedure
const std::shared_ptr<Strategy> select_p =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"p"},
        std::vector<SynonymType>{SynonymType::PROCEDURE},
        std::vector<AttrNameType>{AttrNameType::NONE});

// Select statement
const std::shared_ptr<Strategy> select_s =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"s"},
        std::vector<SynonymType>{SynonymType::STMT},
        std::vector<AttrNameType>{AttrNameType::NONE});

// Select assign
const std::shared_ptr<Strategy> select_a =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"a"},
        std::vector<SynonymType>{SynonymType::ASSIGN},
        std::vector<AttrNameType>{AttrNameType::NONE});

// Select read
const std::shared_ptr<Strategy> select_r =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"r"},
        std::vector<SynonymType>{SynonymType::READ},
        std::vector<AttrNameType>{AttrNameType::NONE});

// Select print
const std::shared_ptr<Strategy> select_pn =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"pn"},
        std::vector<SynonymType>{SynonymType::PRINT},
        std::vector<AttrNameType>{AttrNameType::NONE});

// Select while
const std::shared_ptr<Strategy> select_w =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"w"},
        std::vector<SynonymType>{SynonymType::WHILE},
        std::vector<AttrNameType>{AttrNameType::NONE});

// Select if
const std::shared_ptr<Strategy> select_i =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"i"},
        std::vector<SynonymType>{SynonymType::IF},
        std::vector<AttrNameType>{AttrNameType::NONE});

// Select constant
const std::shared_ptr<Strategy> select_const =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"const"},
        std::vector<SynonymType>{SynonymType::CONSTANT},
        std::vector<AttrNameType>{AttrNameType::NONE});

// Select call
const std::shared_ptr<Strategy> select_c =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"c"},
        std::vector<SynonymType>{SynonymType::CALL},
        std::vector<AttrNameType>{AttrNameType::NONE});

// Select variable
const std::shared_ptr<Strategy> select_v =
    std::make_shared<TupleSelectStrategy>(
        std::vector<std::string>{"v"},
        std::vector<SynonymType>{SynonymType::VARIABLE},
        std::vector<AttrNameType>{AttrNameType::NONE});

}  // namespace Strategies
