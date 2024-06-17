#pragma once

#include <string>

/// @brief A class to read the content of a file
class FileReader {
 private:
  std::string_view filePath;

 public:
  /// @brief Construct a new FileReader object
  /// @param filePath The path to the file to read
  explicit FileReader(std::string_view filePath);

  /// @brief Get the content of the file
  /// @return The content of the file
  std::string getContent() const;
};
