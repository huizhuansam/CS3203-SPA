#include "FileReader.h"

#include "catch.hpp"

TEST_CASE("FileReader can read the content of a file", "[FileReader]") {
  // Note: Assume that unit_testing executable is run from Team10/Code10/build
  // This will NOT work if unit_testing is run from anywhere else
  // The file path below is relative to the build directory
  FileReader fileReaderOK{
      "../src/unit_testing/src/common/fixtures/FileReader.test.txt"};
  // TODO: explore how to make filepath a command line option so we can run the
  // tests from any directory

  SECTION("FileReader reads and returns the contents of a text file") {
    std::string sampleText = "This is a sample text.\n";
    std::string content = fileReaderOK.getContent();
    REQUIRE(content == sampleText);
  }
};

TEST_CASE("FileReader cannot read the content of a file", "[FileReader]") {
  FileReader fileReaderNotFound{
      "../src/unit_testing/src/common/fixtures/NotFound.txt"};

  SECTION("FileReader throws an exception when file is not found") {
    REQUIRE_THROWS_WITH(fileReaderNotFound.getContent(), "File not found");
  }

  // File permission testing is not possible because git is unable to track
  // files without read permission. You just gotta trust me that it works lmao.
};
