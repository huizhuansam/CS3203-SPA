#pragma once

#include <string>

namespace TestSources {

const std::string emptySource = "";

const std::string validSource = R"(
procedure main {
    flag = 0;
    call computeCentroid;
    call printResults;
}

procedure readPoint {
    read x;
    read y;
}
procedure printResults {
    print flag;
      print cenX;
    print cenY;
    print normSq;
}


procedure computeCentroid {
    count = 0;
    cenX = 0;
    cenY = 0;
    call readPoint;
    while ((x != 0) && (y != 0)) {
        count = count + 1;
        cenX = cenX + x;
        cenY = cenY + y;
        call readPoint;
    }
      if (count == 0) then {
        flag = 1;
    } else {
        cenX = cenX / count;
        cenY = cenY / count;
    }
    normSq =
cenX * cenX + cenY * cenY;;;
}
)";

const std::string sourceWithInvalidCharacter = R"(
procedure invalidCharacter {
  # Here is an invalid character
})";

const std::string sourceWithInvalidVariable = R"(
procedure invalidVariable {
  9apple = 0;
})";

const std::string sourceWithInvalidNumber = R"(
procedure invalidNumber {
  x = 01;
})";

}  // namespace TestSources
