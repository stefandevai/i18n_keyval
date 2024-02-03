#include <iostream>
#include <i18n/i18n.hpp>

struct translator
{
  std::string translate(const char* key, std::size_t length) const
  {
    return std::string(key) + " (from app)\n";
  }
};

int main()
{
  using namespace i18n::literals;

  i18n::initialize_translator<translator>();

  std::cout << "animals.cat"_t << '\n';

  return 0;
}
