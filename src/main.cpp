#include <iostream>
#include <i18n/i18n.hpp>
#include <i18n/split_iterator.hpp>

struct translator
{
  std::string translate(const char* key, std::size_t length) const
  {
    return std::string(key) + " (from app)\n";
  }
};

constexpr char default_delimeter[] = ".";

template<const char* delimeter = default_delimeter>
struct test
{
  void print()
  {
    std::cout << "delimeter: " << delimeter << '\n';
  }
};


int main()
{
  using namespace i18n::literals;

  i18n::initialize_translator<translator>();

  // std::cout << "animals.cat"_t << '\n';
  // std::cout << i18n::t("animals.cat") << '\n';

  i18n::split_iterator it{"animals.felines.cat"};
  i18n::split_iterator<':'> it2{"animals:felines:cat"};

  for (; !(*it).empty(); ++it)
  {
    std::cout << *it << '\n';
  }

  for (; !(*it2).empty(); ++it2)
  {
    std::cout << *it2 << '\n';
  }

  return 0;
}
