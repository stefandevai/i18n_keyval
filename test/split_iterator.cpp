#include <i18n/split_iterator.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("split_iterator", "[core]") {
  std::vector<std::string> parts{};

  SECTION("splitting empty") {
    i18n::split_iterator it{""};

    for (; !(*it).empty(); ++it)
    {
      parts.push_back(std::string(*it));
    }

    REQUIRE(parts.empty());
  }

  SECTION("splitting one part") {
    i18n::split_iterator it{"animals"};

    for (; !(*it).empty(); ++it)
    {
      parts.push_back(std::string(*it));
    }

    REQUIRE(parts.size() == 1);
    REQUIRE(parts[0] == "animals");
  }

  SECTION("splitting two parts") {
    i18n::split_iterator it{"animals.felines"};

    for (; !(*it).empty(); ++it)
    {
      parts.push_back(std::string(*it));
    }

    REQUIRE(parts.size() == 2);
    REQUIRE(parts[0] == "animals");
    REQUIRE(parts[1] == "felines");
  }

  SECTION("splitting three parts") {
    i18n::split_iterator it{"animals.felines.cat"};

    for (; !(*it).empty(); ++it)
    {
      parts.push_back(std::string(*it));
    }

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == "animals");
    REQUIRE(parts[1] == "felines");
    REQUIRE(parts[2] == "cat");
  }

  SECTION("using postfix increment") {
    i18n::split_iterator it{"animals.felines.cat"};

    for (; !(*it).empty(); it++)
    {
      parts.push_back(std::string(*it));
    }

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == "animals");
    REQUIRE(parts[1] == "felines");
    REQUIRE(parts[2] == "cat");
  }

  SECTION("splitting with custom delimeter") {
    i18n::split_iterator<':'> it{"animals:felines:cat"};

    for (; !(*it).empty(); ++it)
    {
      parts.push_back(std::string(*it));
    }

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == "animals");
    REQUIRE(parts[1] == "felines");
    REQUIRE(parts[2] == "cat");
  }
}

