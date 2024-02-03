#include <catch2/catch_test_macros.hpp>
#include <i18n/i18n.hpp>
#include <i18n/translators/basic.hpp>

TEST_CASE("translator::basic", "[translators]")
{
  using namespace i18n::literals;

  const i18n::translations translations{
      {"en", {{"moon", "Moon"}, {"sun", "Sun"}}},
      {"es", {{"moon", "Luna"}, {"sun", "Sol"}}},
  };

  i18n::set_locale("");
  i18n::initialize_translator<i18n::translators::basic>(translations);

  REQUIRE("moon"_t == "moon");
  REQUIRE("sun"_t == "sun");
  REQUIRE("star"_t == "star");

  i18n::set_locale("en");

  REQUIRE("moon"_t == "Moon");
  REQUIRE("sun"_t == "Sun");
  REQUIRE("star"_t == "star");

  i18n::set_locale("es");

  REQUIRE("moon"_t == "Luna");
  REQUIRE("sun"_t == "Sol");
  REQUIRE("star"_t == "star");

  i18n::set_locale("en");

  REQUIRE("moon"_t == "Moon");
  REQUIRE("sun"_t == "Sun");
  REQUIRE("star"_t == "star");
}
