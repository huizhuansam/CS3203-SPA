#include "FileReader.h"

#include <fstream>
#include <sstream>

FileReader::FileReader(std::string_view filePath) : filePath(filePath){};

std::string FileReader::getContent() const {
  std::ifstream inputFileStream{static_cast<std::string>(this->filePath),
                                std::ios::in};
  if (!inputFileStream.is_open()) {
    throw std::runtime_error("File not found");
  }
  std::stringstream buffer;
  buffer << inputFileStream.rdbuf();
  inputFileStream.close();
  return buffer.str();
};
