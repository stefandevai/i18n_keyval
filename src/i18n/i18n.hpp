#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include "i18n/registry.hpp"

namespace i18n
{
  const std::filesystem::path default_directory_name{"translations"};

  const std::string default_file_name = "translation";

  std::string t(std::string_view key)
  {
    return registry::instance().translate(key.data(), key.size());
  }

  template <typename T, typename... Args>
  void initialize_translator(Args&&... args)
  {
    auto translator_ = std::make_shared<translator>(T{std::forward<Args>(args)...});
    registry::instance().initialize_translator(std::move(translator_));
  }

  std::string locale()
  {
    return registry::instance().locale;
  }

  void set_locale(std::string locale)
  {
    registry::instance().set_locale(std::move(locale));
  }
}

namespace i18n::literals
{
  std::string operator ""_t(const char* nested_key, std::size_t length)
  {
    return i18n::registry::instance().translate(nested_key, length);
  }
}
