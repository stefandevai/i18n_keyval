#include <iostream>
#include <i18n/i18n.hpp>
#include <translators/nlohmann_json.hpp>
#include <translators/basic.hpp>

int main()
{
  using namespace i18n::literals;

  i18n::translations translations{
    {"en", {
      {"moon", "Moon"},
      {"sun", "Sun"}
    }},
    {"es", {
      {"moon", "Luna"},
      {"sun", "Sol"}
    }},
  };

  i18n::set_locale("en");
  i18n::initialize_translator<i18n::translators::basic_translator>(translations);

  std::cout << "moon"_t << '\n';
  std::cout << "sun"_t << '\n';

  i18n::set_locale("es");

  std::cout << "moon"_t << '\n';
  std::cout << "sun"_t << '\n';

  i18n::set_locale("en");
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

  i18n::set_locale("en");

  std::cout << i18n::t("moon") << '\n';
  std::cout << i18n::t("sun") << '\n';
  std::cout << i18n::t("colors.black") << '\n';
  std::cout << i18n::t("colors.red") << '\n';
  std::cout << i18n::t("animals.felines.cat") << '\n';
  std::cout << i18n::t("animals.felines.tiger") << '\n';
  std::cout << i18n::t("animals.reptiles.crocodile") << '\n';
  std::cout << i18n::t("animals.reptiles.snake") << '\n';

  return 0;
}
