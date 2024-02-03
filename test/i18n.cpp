#include <i18n/i18n.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("i18n", "[core]") {
  i18n::set_locale("");
  auto locale = i18n::locale();

  REQUIRE(locale == "");

  i18n::set_locale("es");
  locale = i18n::locale();

  REQUIRE(locale == "es");
}

