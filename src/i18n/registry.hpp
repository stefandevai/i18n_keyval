#pragma once

#include <memory>

namespace i18n
{
  class translator
  {
  public:
    template<typename T>
    translator(T&& translator_) : _translator(std::make_shared<model<T>>(std::forward<T>(translator_))) {}

    std::string translate(const char* key, const std::size_t length)
    {
      return _translator->translate(key, length);
    }

    struct concept
    {
      virtual ~concept() = default;
      virtual std::string translate(const char* key, const std::size_t length) const = 0;
    };

    template<typename T>
    struct model final : concept
    {
      model(T object_) : _object(std::move(object_)) {}

      std::string translate(const char* key, const std::size_t length) const override
      {
        return _object.translate(key, length);
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
      registry() = default;
      registry(const registry&) = delete;
      registry& operator=(const registry&) = delete;

      void initialize_translator(std::shared_ptr<translator> translator_)
      {
        _translator = std::move(translator_);
      }

      std::string translate(const char* key, const std::size_t length) 
      {
        return _translator->translate(key, length);
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
