#pragma once

#include <memory>
#include <string>

namespace i18n
{
class translator
{
 public:
  template <typename T>
  translator(T&& translator_) : _translator(std::make_shared<model<T>>(std::forward<T>(translator_)))
  {
  }

  void set_locale(const std::string& locale_)
  {
    return _translator->set_locale(locale_);
  }

  std::string translate(const char* composed_key_, const std::size_t length_)
  {
    return _translator->translate(composed_key_, length_);
  }

  struct base
  {
    virtual ~base() = default;
    virtual void set_locale(const std::string& locale_) = 0;
    virtual std::string translate(const char* composed_key_, const std::size_t length_) const = 0;
  };

  template <typename T>
  struct model final : base
  {
    model(T object_) : _object(std::move(object_)) {}

    void set_locale(const std::string& locale_)
    {
      return _object.set_locale(locale_);
    }

    std::string translate(const char* composed_key_, const std::size_t length_) const
    {
      return _object.translate(composed_key_, length_);
    }

   private:
    T _object;
  };

 private:
  std::shared_ptr<base> _translator;
};
}  // namespace i18n
