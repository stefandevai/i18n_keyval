#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>

#include "i18n/split_iterator.hpp"
#include "i18n/utils.hpp"

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
      return;
    }

    const std::filesystem::path full_path = _directory_path / locale / (default_file_name + _file_extension);
    auto json_string = i18n::utils::read_file(full_path);
    _object = nlohmann::json::parse(std::move(json_string));
  }

  std::string translate(const char* composed_key, std::size_t length) const
  {
    std::string_view view{composed_key, length};
    i18n::split_iterator it{view};

    auto* current_object = &_object;

    for (i18n::split_iterator it{view}; !(*it).empty(); ++it)
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
  std::string _file_extension = ".json";
  std::filesystem::path _directory_path;
};
}  // namespace i18n::translators
