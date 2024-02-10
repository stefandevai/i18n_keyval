#include <catch2/catch_test_macros.hpp>
#include <i18n_keyval/core/registry.hpp>

TEST_CASE("registry", "[core]")
{
  i18n::registry::instance().set_locale("");
  auto locale = i18n::registry::instance().locale;

  REQUIRE(locale == "");

  i18n::registry::instance().set_locale("es");
  locale = i18n::registry::instance().locale;

  REQUIRE(locale == "es");
}
