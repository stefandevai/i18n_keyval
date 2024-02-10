#pragma once

#include <filesystem>
#include <string>

#include "i18n_keyval/core/registry.hpp"
#include "i18n_keyval/translators/basic.hpp"

namespace i18n
{
const std::filesystem::path default_directory_name{"translations"};

const std::string default_file_name = "translation";

[[nodiscard]] std::string t(std::string_view key_) noexcept;

[[nodiscard]] std::string t(std::string_view key_, std::size_t count_) noexcept;

template <typename T = translators::basic, typename... Args>
void initialize_translator(Args&&... args_)
{
  auto translator_ = std::make_shared<translator>(T{std::forward<Args>(args_)...});
  registry::instance().initialize_translator(std::move(translator_));
}

std::string locale() noexcept;

void set_locale(std::string locale_);
}  // namespace i18n

namespace i18n::literals
{
[[nodiscard]] inline std::string operator""_t(const char* nested_key_, std::size_t length_) noexcept
{
  return i18n::registry::instance().translate(nested_key_, length_);
}
}  // namespace i18n::literals
