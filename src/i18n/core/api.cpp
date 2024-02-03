#include "i18n/core/api.hpp"

namespace i18n
{
std::string t(std::string_view key)
{
  return registry::instance().translate(key.data(), key.size());
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
