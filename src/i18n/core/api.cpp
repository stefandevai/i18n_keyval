#include "i18n/core/api.hpp"

namespace
{
std::string make_plural_key(std::string_view key)
{
  return std::string(key) + "_plural";
}
}  // namespace

namespace i18n
{
std::string t(std::string_view key)
{
  return registry::instance().translate(key.data(), key.size());
}

std::string t(std::string_view key, std::size_t count)
{
  std::string translation;

  if (count == 1)
  {
    translation = registry::instance().translate(key.data(), key.size());
  }
  else
  {
    const auto plural_key = make_plural_key(key);
    translation = registry::instance().translate(plural_key.c_str(), plural_key.size());
  }

  const auto it = translation.find("{count}");

  if (it == translation.npos)
  {
    return translation;
  }

  return translation.replace(it, 7, std::to_string(count));
}

void set_locale(std::string locale)
{
  registry::instance().set_locale(std::move(locale));
}

std::string locale()
{
  return registry::instance().locale;
}
}  // namespace i18n
