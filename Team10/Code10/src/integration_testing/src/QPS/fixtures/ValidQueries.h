#pragma once

#include <string>

#include "tokenizer/Token.h"

namespace ValidQueries {

const std::string simpleSingleSelectQuery = R"(
procedure p;
Select p such that Calls("ProcA", p)
)";

const std::string simpleBooleanSelectQuery = R"(
constant c1; assign a1;
Select BOOLEAN with c1.value = a1.stmt#
)";

const std::string simpleTupleSelectQuery = R"(
assign a; variable v;
Select <a,v> pattern a(v,_)
)";

const std::string complexQuery = R"(
assign a; while w; procedure p, p1; stmt s; variable v; if ifs; read r; constant const;
Select <p1, a.stmt#, p.procName> pattern a ("count",_"y2%((y2/5)*(7+1))-10+y2"_)
such that Modifies(4,v) and Modifies(p,v) and not Uses(12,v) and Uses("main",v)
such that Follows(a,3) and  Follows*(1,8) and Parent(_,a) such that Parent*(w,a)
such that Calls(p, "fourth") and not Calls*(p,p1) and Next(2,s) and Next*(4,9) and
Affects(2,_) with r.stmt# = const.value and "x" = "x" pattern ifs(v,_,_) and w(_,_)
)";

const std::string queryWithWhitespaces = R"(
assign	 a1  ;
Select   a1     such   that 	not  Affects(  a1 , 17 )
)";

const std::string queryWithKeywordsAsSynonyms = R"(
procedure procName; call not; constant pattern; read with, BOOLEAN, and; print Select; variable Modifies;
Select <Select.stmt#,with> with with.varName = Select.varName and
and.varName = not.procName with procName.procName = "f1fTy" and
pattern.value=BOOLEAN.stmt# such that Modifies(12, Modifies)
)";

}  // namespace ValidQueries
