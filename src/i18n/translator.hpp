#pragma once

#include <string>
#include <memory>

namespace i18n
{
  class translator
  {
  public:
    template<typename T>
    translator(T&& translator_) : _translator(std::make_shared<model<T>>(std::forward<T>(translator_))) {}

    void set_locale(const std::string& locale)
    {
      return _translator->set_locale(locale);
    }

    std::string translate(const char* composed_key, const std::size_t length)
    {
      return _translator->translate(composed_key, length);
    }

    struct base
    {
      virtual ~base() = default;
      virtual void set_locale(const std::string& locale) = 0;
      virtual std::string translate(const char* composed_key, const std::size_t length) const = 0;
    };

    template<typename T>
    struct model final : base
    {
      model(T object_) : _object(std::move(object_)) {}

      void set_locale(const std::string& locale)
      {
        return _object.set_locale(locale);
      }

      std::string translate(const char* composed_key, const std::size_t length) const
      {
        return _object.translate(composed_key, length);
      }

    private:
      T _object;
    };

  private:
    std::shared_ptr<base> _translator;
  };
}

