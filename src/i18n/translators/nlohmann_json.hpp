#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>

#include "i18n/util/extension.hpp"
#include "i18n/util/file.hpp"
#include "i18n/util/split_iterator.hpp"

namespace i18n::translators
{
class nlohmann_json
{
 public:
  nlohmann_json(std::filesystem::path directory_path_ = default_directory_name)
      : _directory_path(std::move(directory_path_))
  {
  }

  void set_locale(const std::string& locale)
  {
    if (locale.empty())
    {
      _object = nlohmann::json{};
      return;
    }

    const std::filesystem::path locale_directory = _directory_path / locale;

    if (!std::filesystem::exists(locale_directory) || !std::filesystem::is_directory(locale_directory))
    {
      _object = nlohmann::json{};
      return;
    }

    const std::filesystem::path full_path = locale_directory / (default_file_name + util::extension::json);

    auto json_string = i18n::util::read_file(full_path);
    _object = nlohmann::json::parse(std::move(json_string));
  }

  std::string translate(const char* composed_key, std::size_t length) const
  {
    std::string_view view{composed_key, length};
    auto* current_object = &_object;

    for (i18n::util::split_iterator it{view}; !(*it).empty(); ++it)
    {
      const std::string_view key = *it;

      if (current_object->contains(key))
      {
        current_object = &((*current_object)[key]);
      }
      else
      {
        return std::string{view};
      }
    }

    if (current_object->is_null() || !current_object->is_string())
    {
      return std::string{view};
    }

    return current_object->get<std::string>();
  }

 private:
  nlohmann::json _object;
  std::filesystem::path _directory_path;
};
}  // namespace i18n::translators
