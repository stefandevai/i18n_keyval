#include <i18n/i18n.hpp>
#include <i18n/translators/nlohmann_json.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("translator::nlohmann_json", "[translators]") {
  using namespace i18n::literals;

  i18n::set_locale("");
  i18n::initialize_translator<i18n::translators::nlohmann_json>();

  REQUIRE("moon"_t == "moon");
  REQUIRE("sun"_t == "sun");
  REQUIRE("star"_t == "star");
  REQUIRE("colors.black"_t == "colors.black");
  REQUIRE("colors.red"_t == "colors.red");
  REQUIRE("colors.white"_t == "colors.white");
  REQUIRE("animals.felines.cat"_t == "animals.felines.cat");
  REQUIRE("animals.felines.tiger"_t == "animals.felines.tiger");
  REQUIRE("animals.felines.jaguar"_t == "animals.felines.jaguar");
  REQUIRE("animals.reptiles.crocodile"_t == "animals.reptiles.crocodile");
  REQUIRE("animals.reptiles.snake"_t == "animals.reptiles.snake");
  REQUIRE("animals.reptiles.lizard"_t == "animals.reptiles.lizard");
  REQUIRE(""_t == "");

  i18n::set_locale("en");

  REQUIRE("moon"_t == "Moon");
  REQUIRE("sun"_t == "Sun");
  REQUIRE("star"_t == "star");
  REQUIRE("colors.black"_t == "Black");
  REQUIRE("colors.red"_t == "Red");
  REQUIRE("colors.white"_t == "colors.white");
  REQUIRE("animals.felines.cat"_t == "Cat");
  REQUIRE("animals.felines.tiger"_t == "Tiger");
  REQUIRE("animals.felines.jaguar"_t == "animals.felines.jaguar");
  REQUIRE("animals.reptiles.crocodile"_t == "Crocodile");
  REQUIRE("animals.reptiles.snake"_t == "Snake");
  REQUIRE("animals.reptiles.lizard"_t == "animals.reptiles.lizard");
  REQUIRE(""_t == "");

  i18n::set_locale("es");

  REQUIRE("moon"_t == "Luna");
  REQUIRE("sun"_t == "Sol");
  REQUIRE("star"_t == "star");
  REQUIRE("colors.black"_t == "Negro");
  REQUIRE("colors.red"_t == "Rojo");
  REQUIRE("colors.white"_t == "colors.white");
  REQUIRE("animals.felines.cat"_t == "Gato");
  REQUIRE("animals.felines.tiger"_t == "Tigre");
  REQUIRE("animals.felines.jaguar"_t == "animals.felines.jaguar");
  REQUIRE("animals.reptiles.crocodile"_t == "Cocodrilo");
  REQUIRE("animals.reptiles.snake"_t == "Víbora");
  REQUIRE("animals.reptiles.lizard"_t == "animals.reptiles.lizard");
  REQUIRE(""_t == "");

  i18n::set_locale("en");

  REQUIRE("moon"_t == "Moon");
  REQUIRE("sun"_t == "Sun");
  REQUIRE("star"_t == "star");
  REQUIRE("colors.black"_t == "Black");
  REQUIRE("colors.red"_t == "Red");
  REQUIRE("colors.white"_t == "colors.white");
  REQUIRE("animals.felines.cat"_t == "Cat");
  REQUIRE("animals.felines.tiger"_t == "Tiger");
  REQUIRE("animals.felines.jaguar"_t == "animals.felines.jaguar");
  REQUIRE("animals.reptiles.crocodile"_t == "Crocodile");
  REQUIRE("animals.reptiles.snake"_t == "Snake");
  REQUIRE("animals.reptiles.lizard"_t == "animals.reptiles.lizard");
}
