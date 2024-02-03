#include <iostream>
#include <i18n/i18n.hpp>
#include <i18n/split_iterator.hpp>
#include <translators/nlohmann_json.hpp>

int main()
{
  using namespace i18n::literals;

  i18n::initialize_translator<i18n::translators::nlohmann_json>();

  std::cout << "English:\n";

  std::cout << "moon"_t << '\n';
  std::cout << "sun"_t << '\n';
  std::cout << "colors.black"_t << '\n';
  std::cout << "colors.red"_t << '\n';
  std::cout << "animals.felines.cat"_t << '\n';
  std::cout << "animals.felines.tiger"_t << '\n';
  std::cout << "animals.reptiles.crocodile"_t << '\n';
  std::cout << "animals.reptiles.snake"_t << '\n';

  i18n::set_locale("es");

  std::cout << "\nEspañol:\n";

  std::cout << "moon"_t << '\n';
  std::cout << "sun"_t << '\n';
  std::cout << "colors.black"_t << '\n';
  std::cout << "colors.red"_t << '\n';
  std::cout << "animals.felines.cat"_t << '\n';
  std::cout << "animals.felines.tiger"_t << '\n';
  std::cout << "animals.reptiles.crocodile"_t << '\n';
  std::cout << "animals.reptiles.snake"_t << '\n';

  return 0;
}
