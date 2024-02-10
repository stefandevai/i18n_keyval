#include <catch2/catch_test_macros.hpp>
#include <i18n_keyval/i18n.hpp>
#include <i18n_keyval/translators/basic.hpp>

TEST_CASE("translator::basic", "[translators]")
{
  using namespace i18n::literals;

  const i18n::translations translations{
      {"en", {{"moon", "Moon"}, {"sun", "Sun"}}},
      {"es", {{"moon", "Luna"}, {"sun", "Sol"}}},
  };

  i18n::set_locale("");
  i18n::initialize_translator(translations);

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

TEST_CASE("translator::basic (plurals)", "[translators]")
{
  using namespace i18n::literals;

  const i18n::translations translations{
      {"en",
       {
           {"moon", "Moon"},
           {"moon_plural", "Moons"},
           {"eating_orange", "Eating {count} orange"},
           {"eating_orange_plural", "Eating {count} oranges"},
       }},
      {"es",
       {
           {"moon", "Luna"},
           {"moon_plural", "Lunas"},
           {"sun", "Sol"},
           {"eating_orange", "Comiendo {count} naranja"},
           {"eating_orange_plural", "Comiendo {count} naranjas"},
       }},
  };

  i18n::set_locale("en");
  i18n::initialize_translator(translations);

  REQUIRE(i18n::t("moon", 0) == "Moons");
  REQUIRE(i18n::t("moon", 1) == "Moon");
  REQUIRE(i18n::t("moon", 2) == "Moons");
  REQUIRE(i18n::t("moon", 9999) == "Moons");
  REQUIRE(i18n::t("eating_orange", 0) == "Eating 0 oranges");
  REQUIRE(i18n::t("eating_orange", 1) == "Eating 1 orange");
  REQUIRE(i18n::t("eating_orange", 3) == "Eating 3 oranges");
  REQUIRE(i18n::t("eating_orange", 9999) == "Eating 9999 oranges");

  i18n::set_locale("es");

  REQUIRE(i18n::t("moon", 0) == "Lunas");
  REQUIRE(i18n::t("moon", 1) == "Luna");
  REQUIRE(i18n::t("moon", 2) == "Lunas");
  REQUIRE(i18n::t("moon", 9999) == "Lunas");
  REQUIRE(i18n::t("eating_orange", 0) == "Comiendo 0 naranjas");
  REQUIRE(i18n::t("eating_orange", 1) == "Comiendo 1 naranja");
  REQUIRE(i18n::t("eating_orange", 3) == "Comiendo 3 naranjas");
  REQUIRE(i18n::t("eating_orange", 9999) == "Comiendo 9999 naranjas");
}
