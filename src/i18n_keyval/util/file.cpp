#include "i18n_keyval/util/file.hpp"

#include <cstring>

namespace i18n::util
{
std::string read_file(const std::filesystem::path filepath)
{
  const auto& filepath_str = filepath.string();
  FILE* file = std::fopen(filepath_str.c_str(), "rt");

  if (file == nullptr)
  {
    return "";
  }

  std::fseek(file, 0, SEEK_END);
  unsigned long length = ftell(file);
  char* data = new char[length + 1];
  std::memset(data, 0, length + 1);
  std::fseek(file, 0, SEEK_SET);
  std::fread(data, 1, length, file);
  std::fclose(file);

  std::string result(data);
  delete[] data;
  return result;
}
}  // namespace i18n::util
