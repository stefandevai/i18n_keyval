#include "i18n/core/api.hpp"

namespace
{
std::string make_plural_key(std::string_view key)
{
  return std::string(key) + "_plural";
}
}

namespace i18n
{
std::string t(std::string_view key)
{
  return registry::instance().translate(key.data(), key.size());
}

std::string t(std::string_view key, std::size_t count)
{
  if (count == 1)
  {
    return registry::instance().translate(key.data(), key.size());
  }

  const auto plural_key = make_plural_key(key);

  return registry::instance().translate(plural_key.c_str(), plural_key.size());
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
