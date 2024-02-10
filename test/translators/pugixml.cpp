#include <catch2/catch_test_macros.hpp>
#include <i18n_keyval/i18n.hpp>
#include <i18n_keyval/translators/pugixml.hpp>

TEST_CASE("translator::pugixml", "[translators]")
{
  using namespace i18n::literals;

  i18n::set_locale("");
  i18n::initialize_translator<i18n::translators::pugixml>();

  REQUIRE("moon"_t == "moon");
  REQUIRE("sun"_t == "sun");
  REQUIRE("star"_t == "star");
  REQUIRE("colors/black"_t == "colors/black");
  REQUIRE("colors/red"_t == "colors/red");
  REQUIRE("colors/white"_t == "colors/white");
  REQUIRE("animals/felines/cat"_t == "animals/felines/cat");
  REQUIRE("animals/felines/tiger"_t == "animals/felines/tiger");
  REQUIRE("animals/felines/jaguar"_t == "animals/felines/jaguar");
  REQUIRE("animals/reptiles/crocodile"_t == "animals/reptiles/crocodile");
  REQUIRE("animals/reptiles/snake"_t == "animals/reptiles/snake");
  REQUIRE("animals/reptiles/lizard"_t == "animals/reptiles/lizard");
  REQUIRE(""_t == "");

  REQUIRE(i18n::t("moon") == "moon");
  REQUIRE(i18n::t("sun") == "sun");
  REQUIRE(i18n::t("star") == "star");
  REQUIRE(i18n::t("colors/black") == "colors/black");
  REQUIRE(i18n::t("colors/red") == "colors/red");
  REQUIRE(i18n::t("colors/white") == "colors/white");
  REQUIRE(i18n::t("animals/felines/cat") == "animals/felines/cat");
  REQUIRE(i18n::t("animals/felines/tiger") == "animals/felines/tiger");
  REQUIRE(i18n::t("animals/felines/jaguar") == "animals/felines/jaguar");
  REQUIRE(i18n::t("animals/reptiles/crocodile") == "animals/reptiles/crocodile");
  REQUIRE(i18n::t("animals/reptiles/snake") == "animals/reptiles/snake");
  REQUIRE(i18n::t("animals/reptiles/lizard") == "animals/reptiles/lizard");
  REQUIRE(i18n::t("") == "");

  i18n::set_locale("en");

  REQUIRE("moon"_t == "Moon");
  REQUIRE("sun"_t == "Sun");
  REQUIRE("star"_t == "star");
  REQUIRE("colors/black"_t == "Black");
  REQUIRE("colors/red"_t == "Red");
  REQUIRE("colors/white"_t == "colors/white");
  REQUIRE("animals/felines/cat"_t == "Cat");
  REQUIRE("animals/felines/tiger"_t == "Tiger");
  REQUIRE("animals/felines/jaguar"_t == "animals/felines/jaguar");
  REQUIRE("animals/reptiles/crocodile"_t == "Crocodile");
  REQUIRE("animals/reptiles/snake"_t == "Snake");
  REQUIRE("animals/reptiles/lizard"_t == "animals/reptiles/lizard");
  REQUIRE(""_t == "");

  REQUIRE(i18n::t("moon") == "Moon");
  REQUIRE(i18n::t("sun") == "Sun");
  REQUIRE(i18n::t("star") == "star");
  REQUIRE(i18n::t("colors/black") == "Black");
  REQUIRE(i18n::t("colors/red") == "Red");
  REQUIRE(i18n::t("colors/white") == "colors/white");
  REQUIRE(i18n::t("animals/felines/cat") == "Cat");
  REQUIRE(i18n::t("animals/felines/tiger") == "Tiger");
  REQUIRE(i18n::t("animals/felines/jaguar") == "animals/felines/jaguar");
  REQUIRE(i18n::t("animals/reptiles/crocodile") == "Crocodile");
  REQUIRE(i18n::t("animals/reptiles/snake") == "Snake");
  REQUIRE(i18n::t("animals/reptiles/lizard") == "animals/reptiles/lizard");
  REQUIRE(i18n::t("") == "");

  i18n::set_locale("es");

  REQUIRE("moon"_t == "Luna");
  REQUIRE("sun"_t == "Sol");
  REQUIRE("star"_t == "star");
  REQUIRE("colors/black"_t == "Negro");
  REQUIRE("colors/red"_t == "Rojo");
  REQUIRE("colors/white"_t == "colors/white");
  REQUIRE("animals/felines/cat"_t == "Gato");
  REQUIRE("animals/felines/tiger"_t == "Tigre");
  REQUIRE("animals/felines/jaguar"_t == "animals/felines/jaguar");
  REQUIRE("animals/reptiles/crocodile"_t == "Cocodrilo");
  REQUIRE("animals/reptiles/snake"_t == "Víbora");
  REQUIRE("animals/reptiles/lizard"_t == "animals/reptiles/lizard");
  REQUIRE(""_t == "");

  REQUIRE(i18n::t("moon") == "Luna");
  REQUIRE(i18n::t("sun") == "Sol");
  REQUIRE(i18n::t("star") == "star");
  REQUIRE(i18n::t("colors/black") == "Negro");
  REQUIRE(i18n::t("colors/red") == "Rojo");
  REQUIRE(i18n::t("colors/white") == "colors/white");
  REQUIRE(i18n::t("animals/felines/cat") == "Gato");
  REQUIRE(i18n::t("animals/felines/tiger") == "Tigre");
  REQUIRE(i18n::t("animals/felines/jaguar") == "animals/felines/jaguar");
  REQUIRE(i18n::t("animals/reptiles/crocodile") == "Cocodrilo");
  REQUIRE(i18n::t("animals/reptiles/snake") == "Víbora");
  REQUIRE(i18n::t("animals/reptiles/lizard") == "animals/reptiles/lizard");
  REQUIRE(i18n::t("") == "");

  i18n::set_locale("en");

  REQUIRE("moon"_t == "Moon");
  REQUIRE("sun"_t == "Sun");
  REQUIRE("star"_t == "star");
  REQUIRE("colors/black"_t == "Black");
  REQUIRE("colors/red"_t == "Red");
  REQUIRE("colors/white"_t == "colors/white");
  REQUIRE("animals/felines/cat"_t == "Cat");
  REQUIRE("animals/felines/tiger"_t == "Tiger");
  REQUIRE("animals/felines/jaguar"_t == "animals/felines/jaguar");
  REQUIRE("animals/reptiles/crocodile"_t == "Crocodile");
  REQUIRE("animals/reptiles/snake"_t == "Snake");
  REQUIRE("animals/reptiles/lizard"_t == "animals/reptiles/lizard");

  REQUIRE(i18n::t("moon") == "Moon");
  REQUIRE(i18n::t("sun") == "Sun");
  REQUIRE(i18n::t("star") == "star");
  REQUIRE(i18n::t("colors/black") == "Black");
  REQUIRE(i18n::t("colors/red") == "Red");
  REQUIRE(i18n::t("colors/white") == "colors/white");
  REQUIRE(i18n::t("animals/felines/cat") == "Cat");
  REQUIRE(i18n::t("animals/felines/tiger") == "Tiger");
  REQUIRE(i18n::t("animals/felines/jaguar") == "animals/felines/jaguar");
  REQUIRE(i18n::t("animals/reptiles/crocodile") == "Crocodile");
  REQUIRE(i18n::t("animals/reptiles/snake") == "Snake");
  REQUIRE(i18n::t("animals/reptiles/lizard") == "animals/reptiles/lizard");

  i18n::set_locale("fr");

  REQUIRE("moon"_t == "moon");
  REQUIRE("sun"_t == "sun");
  REQUIRE("star"_t == "star");
  REQUIRE("colors/black"_t == "colors/black");
  REQUIRE("colors/red"_t == "colors/red");
  REQUIRE("colors/white"_t == "colors/white");
  REQUIRE("animals/felines/cat"_t == "animals/felines/cat");
  REQUIRE("animals/felines/tiger"_t == "animals/felines/tiger");
  REQUIRE("animals/felines/jaguar"_t == "animals/felines/jaguar");
  REQUIRE("animals/reptiles/crocodile"_t == "animals/reptiles/crocodile");
  REQUIRE("animals/reptiles/snake"_t == "animals/reptiles/snake");
  REQUIRE("animals/reptiles/lizard"_t == "animals/reptiles/lizard");
  REQUIRE(""_t == "");

  REQUIRE(i18n::t("moon") == "moon");
  REQUIRE(i18n::t("sun") == "sun");
  REQUIRE(i18n::t("star") == "star");
  REQUIRE(i18n::t("colors/black") == "colors/black");
  REQUIRE(i18n::t("colors/red") == "colors/red");
  REQUIRE(i18n::t("colors/white") == "colors/white");
  REQUIRE(i18n::t("animals/felines/cat") == "animals/felines/cat");
  REQUIRE(i18n::t("animals/felines/tiger") == "animals/felines/tiger");
  REQUIRE(i18n::t("animals/felines/jaguar") == "animals/felines/jaguar");
  REQUIRE(i18n::t("animals/reptiles/crocodile") == "animals/reptiles/crocodile");
  REQUIRE(i18n::t("animals/reptiles/snake") == "animals/reptiles/snake");
  REQUIRE(i18n::t("animals/reptiles/lizard") == "animals/reptiles/lizard");
  REQUIRE(i18n::t("") == "");
}

TEST_CASE("translator::pugixml (custom directory)", "[translators]")
{
  using namespace i18n::literals;

  i18n::set_locale("en");
  i18n::initialize_translator<i18n::translators::pugixml>("data/translations");

  REQUIRE("moon"_t == "Moon");
}

TEST_CASE("translator::pugixml (plurals)", "[translators]")
{
  using namespace i18n::literals;

  i18n::set_locale("en");
  i18n::initialize_translator<i18n::translators::pugixml>();

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
