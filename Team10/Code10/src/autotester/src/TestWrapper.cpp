#include "TestWrapper.h"

#include "FileReader.h"
#include "PKB.h"
#include "QPS.h"
#include "SP.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() : programKnowledgeBase(PKB::getPKB()) {}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
  FileReader fileReader{filename};
  std::string content = fileReader.getContent();
  SP::SP::processSimple(content);
  return;
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results) {
  results = QPS::QPS::evaluate(query);
  return;
}
