#pragma once

#include <memory>
#include <string>
#include <vector>

#include "tokenizer/Token.h"

namespace TestQueries {

const std::string emptyQuery = "";

const std::string whitespaceQuery = R"(

)";

const std::string queryWithInvalidChar = R"(
variable v;!
Select v
)";

const std::string queryWithInvalidName = R"(
variable 7v;
Select v
)";

const std::string queryWithInvalidInteger = R"(
variable v; pattern a;
Select v pattern a(_, "03")
)";

const std::string simpleTupleQuery = R"(
assign a; variable v;
Select <a, v>
)";

const std::string tupleQueryWithAttr = R"(
procedure p; assign a; variable v; constant cnst;
Select <p.procName, a.stmt#, v.varName, cnst.value>
)";

const std::string tupleQueryWithInvalidAttr = R"(
read re;
Select <re.procValue>
)";

const std::string tupleQueryWithoutAttrAfterPeriod = R"(
print pn;
Select <pn.>
)";

const std::string simpleWithQuery = R"(
stmt s;
Select s with s.stmt# = 1
)";

const std::string complexValidQuery = R"(
assign a; while w;
Select a such that Parent* (w, a) pattern a ("count", _)
)";

const std::string complexValidQuery2 = R"(
assign a;
Select a pattern a ( "normSq" , _"cenX * cenX"_)
)";
}  // namespace TestQueries
