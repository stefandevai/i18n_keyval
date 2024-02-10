#pragma once

#include <string>
#include <unordered_map>

#include "i18n_keyval/core/common.hpp"

namespace i18n
{
using translation_table = std::unordered_map<std::string, std::string>;
using translations = std::unordered_map<std::string, translation_table>;
}  // namespace i18n

namespace i18n::translators
{
class basic
{
 public:
  basic(translations translations_) : _translations(std::move(translations_)) {}

  void set_locale(const std::string& locale_)
  {
    if (_translations.find(locale_) == _translations.end())
    {
      throw_i18n_exception("Locale not found");
      return;
    }

    _values = &_translations.at(locale_);
  }

  std::string translate(const char* key_, std::size_t length_) const noexcept
  {
    std::string_view view{key_, length_};

    if (_values == nullptr)
    {
      return std::string{view};
    }

    const auto& values = *_values;

    if (values.find(key_) == values.end())
    {
      return std::string{view};
    }

    return values.at(key_);
  }

 private:
  translations _translations;
  translation_table* _values = nullptr;
};
}  // namespace i18n::translators
