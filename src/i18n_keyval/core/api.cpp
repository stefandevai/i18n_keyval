#include "i18n_keyval/core/api.hpp"

namespace
{
std::string make_plural_key(std::string_view key_) noexcept
{
  return std::string(key_) + "_plural";
}
}  // namespace

namespace i18n
{
std::string t(std::string_view key_) noexcept
{
  return registry::instance().translate(key_.data(), key_.size());
}

std::string t(std::string_view key_, std::size_t count_) noexcept
{
  std::string translation;

  if (count_ == 1)
  {
    translation = registry::instance().translate(key_.data(), key_.size());
  }
  else
  {
    const auto plural_key = make_plural_key(key_);
    translation = registry::instance().translate(plural_key.c_str(), plural_key.size());
  }

  const auto it = translation.find("{count}");

  if (it == translation.npos)
  {
    return translation;
  }

  return translation.replace(it, 7, std::to_string(count_));
}

void set_locale(std::string locale_)
{
  registry::instance().set_locale(std::move(locale_));
}

std::string locale() noexcept
{
  return registry::instance().locale;
}
}  // namespace i18n
