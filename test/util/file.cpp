#include <catch2/catch_test_macros.hpp>
#include <i18n_keyval/util/file.hpp>

TEST_CASE("reading file", "[core]")
{
  const auto filepath = std::filesystem::path{"data/dummy.txt"};
  const auto content = i18n::util::read_file(filepath);

  REQUIRE(content == "dummy content\n");
}
