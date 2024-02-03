#include "i18n/registry.hpp"

namespace i18n
{
  void registry::initialize_translator(std::shared_ptr<translator> translator_)
  {
    _translator = std::move(translator_);
    _translator->set_locale(locale);
  }

  std::string registry::translate(const char* composed_key, const std::size_t length) 
  {
    if (_translator == nullptr)
    {
      return std::string{composed_key, length};
    }

    return _translator->translate(composed_key, length);
  }

  void registry::set_locale(std::string locale_)
  {
    locale = std::move(locale_);

    if (_translator != nullptr)
    {
      _translator->set_locale(locale);
    }
  }

  registry& registry::instance()
  {
    static registry _instance;
    return _instance;
  }
}
