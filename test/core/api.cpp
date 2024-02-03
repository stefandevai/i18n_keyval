#include <catch2/catch_test_macros.hpp>
#include <i18n/core/api.hpp>
#include <string>
#include <unordered_map>

struct translator
{
  std::string locale{};
  std::unordered_map<std::string, std::string> en_translations{{"moon", "Moon"}};
  std::unordered_map<std::string, std::string> es_translations{{"moon", "Luna"}};

  void set_locale(const std::string& locale)
  {
    this->locale = locale;
  }

  std::string translate(const char* key, std::size_t) const
  {
    if (locale == "en")
    {
      return en_translations.at(std::string(key));
    }
    else if (locale == "es")
    {
      return es_translations.at(std::string(key));
    }

    return std::string(key);
  }
};

TEST_CASE("i18n", "[core]")
{
  i18n::set_locale("");
  auto locale = i18n::locale();

  REQUIRE(locale == "");

  i18n::set_locale("es");
  locale = i18n::locale();

  REQUIRE(locale == "es");
}

TEST_CASE("custom translator", "[core]")
{
  using namespace i18n::literals;

  i18n::initialize_translator<translator>();

  i18n::set_locale("en");
  REQUIRE("moon"_t == "Moon");

  i18n::set_locale("es");
  REQUIRE("moon"_t == "Luna");
}
