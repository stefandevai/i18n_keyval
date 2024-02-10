#include "i18n_keyval/core/registry.hpp"

namespace i18n
{
void registry::initialize_translator(std::shared_ptr<translator> translator_)
{
  _translator = std::move(translator_);
  _translator->set_locale(locale);
}

std::string registry::translate(const char* composed_key_, const std::size_t length_) noexcept
{
  if (_translator == nullptr)
  {
    return std::string{composed_key_, length_};
  }

  return _translator->translate(composed_key_, length_);
}

void registry::set_locale(std::string locale_) noexcept
{
  locale = std::move(locale_);

  if (_translator != nullptr)
  {
    _translator->set_locale(locale);
  }
}

registry& registry::instance() noexcept
{
  static registry _instance;
  return _instance;
}
}  // namespace i18n
