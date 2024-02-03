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

    void initialize()
    {
      return _translator->initialize();
    }

    std::string translate(const char* composed_key, const std::size_t length)
    {
      return _translator->translate(composed_key, length);
    }

    struct concept
    {
      virtual ~concept() = default;
      virtual void initialize() = 0;
      virtual std::string translate(const char* composed_key, const std::size_t length) const = 0;
    };

    template<typename T>
    struct model final : concept
    {
      model(T object_) : _object(std::move(object_)) {}

      void initialize() override
      {
        return _object.initialize();
      }

      std::string translate(const char* composed_key, const std::size_t length) const override
      {
        return _object.translate(composed_key, length);
      }

    private:
      T _object;
    };

  private:
    std::shared_ptr<concept> _translator;
  };

  class registry
  {
    public:
      std::string locale = "en";

      registry() = default;
      registry(const registry&) = delete;
      registry& operator=(const registry&) = delete;

      void initialize_translator(std::shared_ptr<translator> translator_)
      {
        _translator = std::move(translator_);
        _translator->initialize();
      }

      std::string translate(const char* composed_key, const std::size_t length) 
      {
        return _translator->translate(composed_key, length);
      }

      void set_locale(const std::string& locale_)
      {
        locale = locale_;
        _translator->initialize();
      }

      static registry& instance()
      {
        static registry _instance;
        return _instance;
      }

    private:
      std::shared_ptr<translator> _translator;
  };
}
