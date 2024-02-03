#include "i18n/util/file.hpp"

namespace i18n::util
{
std::string read_file(const std::filesystem::path filepath)
{
  FILE* file = fopen(filepath.c_str(), "rt");

  if (file == nullptr)
  {
    return "";
  }

  fseek(file, 0, SEEK_END);
  unsigned long length = ftell(file);
  char* data = new char[length + 1];
  memset(data, 0, length + 1);
  fseek(file, 0, SEEK_SET);
  fread(data, 1, length, file);
  fclose(file);

  std::string result(data);
  delete[] data;
  return result;
}
}  // namespace i18n::utils
