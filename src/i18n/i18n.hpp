#pragma once

#include <filesystem>
#include <string>

#include "i18n/registry.hpp"
#include "i18n/translators/basic.hpp"

namespace i18n
{
const std::filesystem::path default_directory_name{"translations"};

const std::string default_file_name = "translation";

std::string t(std::string_view key);

template <typename T = translators::basic, typename... Args>
void initialize_translator(Args&&... args)
{
  auto translator_ = std::make_shared<translator>(T{std::forward<Args>(args)...});
  registry::instance().initialize_translator(std::move(translator_));
}

std::string locale();

void set_locale(std::string locale);
}  // namespace i18n

namespace i18n::literals
{
inline std::string operator""_t(const char* nested_key, std::size_t length)
{
  return i18n::registry::instance().translate(nested_key, length);
}
}  // namespace i18n::literals
