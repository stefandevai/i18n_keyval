#pragma once

#include <string>
#include <iostream>
#include "i18n/registry.hpp"

namespace i18n
{
  const std::string _get_value(const std::string_view key, const char delimeter)
  {
    std::size_t from = 0;

    for (std::size_t i = 0; i < key.size(); i++)
    {
      if (key[i] == delimeter)
      {
        // callback(key.substr(from, i - from));
        from = i + 1;
      }
    }

    if (from < key.size())
    {
      // callback(key.substr(from));
    }

    return std::string(key);
  }

  template <typename T>
  void initialize_translator()
  {
    auto translator_ = std::make_shared<translator>(T{});
    registry::instance().initialize_translator(std::move(translator_));
  }
}

namespace i18n::literals
{
  std::string operator ""_t(const char* nested_key, std::size_t length)
  {
    return i18n::registry::instance().translate(nested_key, length);
    // constexpr char delimeter = '.';

    // backend::object* object = nullptr;

    // return _get_value(nested_key, delimeter);
    
    // _parts(nested_key, delimeter, [&object](std::string_view key)
    // {
    //   if (!backend.contains(key))
    //   {
    //     object = nullptr;
    //     return false;
    //   }
    //
    //   object = backend.get_object_ptr(key);
    //
    //   return true;
    // });

    // return "";
  }
}
