#pragma once

#include <unordered_map>
#include <string>

namespace i18n
{
  using translation_table = std::unordered_map<std::string, std::string>;
  using translations = std::unordered_map<std::string, translation_table>;
}

namespace i18n::translators
{
class basic
{
public:
  basic(translations translations_)
    : _translations(std::move(translations_))
  { }

  void set_locale(const std::string& locale)
  {
    if (!_translations.contains(locale))
    {
      return;
    }

    _values = &_translations.at(locale);
  }

  std::string translate(const char* key, std::size_t length) const
  {
    std::string_view view{key, length};

    if (_values == nullptr)
    {
      return std::string{view};
    }

    const auto& values = *_values;

    if (!values.contains(key))
    {
      return std::string{view};
    }

    return values.at(key);
  }

private:
  translations _translations;
  translation_table* _values = nullptr;
};
}
